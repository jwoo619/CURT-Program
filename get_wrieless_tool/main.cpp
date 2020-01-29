#include "mainwindow.h"
#include <QApplication>

static QString wifi_chip;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
