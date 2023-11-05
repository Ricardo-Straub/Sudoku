#include "mainwindow.h"
#include "menuwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    menuwindow m;
    MainWindow w;
    m.show();
    m.setMainWindow(&w);

    return a.exec();
}
