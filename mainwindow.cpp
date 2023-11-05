#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <bits/stdc++.h>

#include "menuwindow.h"
#include <iostream>
#include <string>
#include <QFrame>
#include <QLabel>
#include <QLayout>




void removeDigits();
void shuffle();
void createDiagonal();
void initMatrix();

bool findNext(int& row, int& column);
bool checkRow(int row, int number);
bool checkColumn(int column, int number);
bool checkBlock(int addRow, int addColumn, int number);
bool check(int row, int column, int number);
bool solve();

int getNextMatrixValue(int i);

#define availabeGuesses 5


QString currentNumber;
QTextEdit* currentBox;
int matrix [9][9];
int solution[9][9];
int nrRemoveDigits = 40;
int nrPlayers = 2;
int currentPlayer = 0;
int nrGuesses = availabeGuesses;
int playerGuesses[availabeGuesses];// same value <- 5
QLabel* playerLabels[4];
int playerScores[availabeGuesses];

int shuffleArray[] = {1,2,3,4,5,6,7,8,9};



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand((unsigned) time(NULL));
    initMatrix();
    createDiagonal();
    bool solved = false;
    while (!solved) {
        solved = solve();
        if (countSolutions() > 1) {
            solved = false;
        }
    }


    if (solved) {
        //copy matrix to solution
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                solution[i][j] = matrix[i][j];
            }
        }
        removeDigits();
        //asign numbers with signal
        QPushButton* numbers[9];
        for (int i = 0; i < 9; i++) {
            QString numberName = "number_" + QString::number(i + 1);
            numbers[i] = MainWindow::findChild<QPushButton*>(numberName);
            connect(numbers[i], SIGNAL(released()), this, SLOT(numberClicked()));
        }
        //asign boxes with signal
        QTextEdit* boxes[81];
        for (int i = 0; i < 81; i++) {
            QString boxName = "b" + QString::number(i + 1);
            QTextEdit* box = MainWindow::findChild<QTextEdit*>(boxName);
            box->setReadOnly(true);
            //box->setText(QString::number(getNextMatrixValue(i)));
            boxes[i] = box;
            connect(box, SIGNAL(selectionChanged()), this, SLOT(boxClicked()));
        }
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                QString boxName = "b" + QString::number(((i*9) + j + 1));
                QTextEdit* box = MainWindow::findChild<QTextEdit*>(boxName);
                //wenn nicht 0
                if (matrix[i][j]) box->setText(QString::number(matrix[i][j]));

            }
        }
    }




}

MainWindow::~MainWindow()
{
    delete ui;
}

//not used
int MainWindow::getNextMatrixValue(int i) {
    return matrix[i / 9][i % 9];
}

void MainWindow::numberClicked() {
    if (!currentBox) return;
    QPushButton* number = (QPushButton*) sender();
    currentNumber = number->text();
    int cellId = currentBox->objectName().mid(1).toInt();

    int i = (cellId / 9);
    int j = cellId % 9;
    if (j != 0) {
        j = j - 1;
    }
    bool doubleGuess = false;
    for (int i = 0; i < availabeGuesses; i++) {
        if (playerGuesses[i] == currentNumber.toInt())  {
            doubleGuess = true;
        }
    }
    if (doubleGuess) {
        for (int i = 0; i < availabeGuesses; i++) {
            playerGuesses[i] = 0;
        }
    } else {
        playerGuesses[availabeGuesses - nrGuesses] = currentNumber.toInt();
    }


    //richtig gearaten
    if (currentNumber.toInt() == solution[i][j] && !doubleGuess) {

        currentBox->setText(currentNumber);
        playerScores[currentPlayer] += currentNumber.toInt();

        nrGuesses--;
        printf("Guesses: %d", nrGuesses);
        //keine versuche mehr
        if (nrGuesses == 0) {
            playerLabels[currentPlayer]->setText("Player"+QString::number(currentPlayer + 1)+
                                                 "| Score: "+QString::number(playerScores[currentPlayer]));
            currentPlayer = ((currentPlayer + 1) % nrPlayers);
            nrGuesses = availabeGuesses;
            playerLabels[currentPlayer]->
                setText("->Player"+QString::number(currentPlayer + 1)+
                                                 "| Guess: "+QString::number(nrGuesses)+
                                                 " Score: "+QString::number(playerScores[currentPlayer]));
        }
        //richtig geraten und nochmal dran
        else {
            playerLabels[currentPlayer]->
                setText("->Player"+QString::number(currentPlayer + 1)+
                        "| Guess: "+QString::number(nrGuesses)+
                        " Score: "+QString::number(playerScores[currentPlayer]));
        }

    }
    //falsch geraten / zahl schon geraten
    else {
        for (int i = 0; i < availabeGuesses; i++) {
            playerGuesses[i] = 0;
        }
        //falsch geraten oder selbe zahl
        playerLabels[currentPlayer]->setText("Player"+QString::number(currentPlayer + 1)+
                                             "| Score: "+QString::number(playerScores[currentPlayer]));
        currentPlayer = ((currentPlayer + 1) % nrPlayers);
        nrGuesses = availabeGuesses;
        playerLabels[currentPlayer]->
            setText("->Player"+QString::number(currentPlayer + 1)+
                    "| Guess: "+QString::number(nrGuesses)+
                    " Score: "+QString::number(playerScores[currentPlayer]));
    }

}

void MainWindow::boxClicked() {

    QTextEdit* box = (QTextEdit*) sender();
    if (currentBox != NULL) {
        currentBox->setStyleSheet("background-color: white;");
    }
    currentBox = box;
    currentBox->setStyleSheet("background-color: lightblue;");
}


void MainWindow::initMatrix() {
    for (int i = 0; i < 9; i++) {
        for (int k = 0; k < 9; k++) {
            matrix[i][k] = 0;
        }
    }
}

void MainWindow::shuffle() {
    printf("shuffle");
    unsigned seed = 0;
    std::shuffle(shuffleArray, shuffleArray + 9,
            std::default_random_engine(seed));
}

void MainWindow::createDiagonal() {
    int count = 0;
    shuffle();
    for (int i = 0; i < 9; i++) {
        for (int k = 0; k < 9; k++) {
            //block links oben
            if (i < 3 && k < 3) {
                matrix[i][k] = shuffleArray[count++];
            }
            //block mitte
            if (i > 2 && i < 6 && k < 6 && k > 2) {
                matrix[i][k] = shuffleArray[count++];
            }
            //unten rechts
            if (i > 5 && k > 5) {
                matrix[i][k] = shuffleArray[count++];
            }
        }
        if (count > 8) {
            count = 0;
            shuffle();
        }
    }
}

bool MainWindow::findNext(int& row, int& column) {
    for (row = 0; row < 9; row++)
        for (column = 0; column < 9; column++)
            if (matrix[row][column] == 0)
                return true;
    return false;
}

bool MainWindow::check(int row, int column, int number)  {
    // true: sicher false: fehler
    return !checkRow(row, number)
           && !checkColumn(column, number)
           && !checkBlock(row - row % 3,
                         column - column % 3, number)
           && matrix[row][column] == 0;;
}

bool MainWindow::checkRow(int row, int number) {
    for (int column = 0; column < 9; column++)
        if (matrix[row][column] == number)
            return true;
    return false;
}

bool MainWindow::checkColumn(int column, int number) {
    for (int row = 0; row < 9; row++) {
        if (matrix[row][column] == number) {
            return true;
        }
    }
    return false;
}


bool MainWindow::checkBlock(int addBlockRow, int addBlockColumn, int number) {
    for (int row = 0; row < 3; row++)
        for (int column = 0; column < 3; column++)
            if (matrix[row + addBlockRow]
                    [column + addBlockColumn] ==
                number)
                return true;
    return false;
}

bool MainWindow::solve() {
    int row = 0;
    int column = 0;
    if (!findNext(row, column)) {
        return true;
    }
    for (int number = 1; number <= 9; number++) {
        if (check(row, column, number)) {
            matrix[row][column] = number;

            if (solve())
                return true;

            matrix[row][column] = 0;
        }
    }
    return false;
}

void MainWindow::removeDigits() {
    int count = nrRemoveDigits;
    while (count != 0) {
        int cellId = std::rand() % 81;
        int i = (cellId / 9);
        int j = cellId % 9;
        if (j != 0) {
            j = j - 1;
        }
        if (matrix[i][j] != 0) {
            count--;
            matrix[i][j] = 0;
        }
    }
}

int MainWindow::countSolutions(int row, int column) {
    if (row == 9 - 1 && column == 9)
        return 1;

    if (column == 9) {
        row++;
        column = 0;
    }
    if (matrix[row][column] > 0)
        return countSolutions(row, column + 1);
    int count = 0;
    for (int num = 1; num <= 9; num++) {
        if (check(row, column, num)) {
            matrix[row][column] = num;

            count += countSolutions(row, column + 1);
        }

        matrix[row][column] = 0;
    }
    return count;
}

void MainWindow::setReceivedValue(int value) {
    nrPlayers = value;
    printf("Goooot valllue !!!!!    %d", value);
    QFrame* pScoreFrame = ui->scoreFrame;
    for (int i = 0; i < nrPlayers; i++) {
        QLabel *label = new QLabel("Player" + QString::number(i + 1), pScoreFrame);
        playerLabels[i] = label;
        label->setGeometry(label->x(), (25 * i), 400, label->height());
        QLayout *frameLayout = pScoreFrame->layout();
       // frameLayout->addWidget(label); brauch man  nicht parent schon gegeben
    }
    playerLabels[0]->setText("->Player"+QString::number(currentPlayer + 1)+
                             "| Guess: "+QString::number(nrGuesses)+
                             " Score: "+QString::number(playerScores[currentPlayer]));

}



