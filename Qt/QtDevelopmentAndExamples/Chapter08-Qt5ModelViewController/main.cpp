#include "mainwindow.h"
#include "dirmodeex.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    DirModeEx w;
    w.show();
    return a.exec();
}
