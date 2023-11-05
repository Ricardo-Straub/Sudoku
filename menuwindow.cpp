#include "menuwindow.h"
#include "qpushbutton.h"
#include "ui_menuwindow.h"
#include "mainwindow.h"

#include <QObject>  // for connecting signals and slots
#include <QDebug>

void onButtonClicked();
void setMainWindow(MainWindow* mainwindow);
MainWindow* m;

menuwindow::menuwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menuwindow)

{
    ui->setupUi(this);
    QPushButton* pl1 = menuwindow::findChild<QPushButton*>("pl1");
    QPushButton *pl2 = menuwindow::findChild<QPushButton*>("pl2");
    QPushButton *pl3 = menuwindow::findChild<QPushButton*>("pl3");
    QPushButton *pl4 = menuwindow::findChild<QPushButton*>("pl4");

    connect(pl1, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pl2, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pl3, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(pl4, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
}

menuwindow::~menuwindow()
{
    delete ui;
}

void menuwindow::setMainWindow(MainWindow* mainwindow) {
    m = mainwindow;
}

void menuwindow::onButtonClicked() {
    int value = 42;
    QPushButton* btn = (QPushButton*) sender();
    if (btn->objectName().compare("pl1") == 0) value = 1;
    if (btn->objectName().compare("pl2") == 0) value = 2;
    if (btn->objectName().compare("pl3") == 0) value = 3;
    if (btn->objectName().compare("pl4") == 0) value = 4;

    m->setReceivedValue(value);
    m->show();
    this->close();

}

