#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class menuwindow;
}

class menuwindow : public QDialog
{
    Q_OBJECT

public:
    explicit menuwindow(QWidget *parent = nullptr);
    ~menuwindow();
    int nrOfPlayers = 0;
    void setMainWindow(MainWindow* mainwindow);

private:
    Ui::menuwindow *ui;

signals:
    void buttonClicked(int variableValue);

private slots:
    void onButtonClicked();
};

#endif // MENUWINDOW_H
