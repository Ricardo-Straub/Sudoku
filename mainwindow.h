#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void shuffle();
    void createDiagonal();
    void initMatrix();
    void removeDigits();
    bool findNext(int& row, int& column);
    bool checkRow(int row, int number);
    bool checkColumn(int column, int number);
    bool checkBlock(int addRow, int addColumn, int number);
    bool check(int row, int column, int number);
    bool solve();
    void setReceivedValue(int value);
    int countSolutions(int row = 0, int column = 0);


    int getNextMatrixValue(int i);

private:
    Ui::MainWindow *ui;


private slots:
    void boxClicked();
    void numberClicked();
};
#endif // MAINWINDOW_H
