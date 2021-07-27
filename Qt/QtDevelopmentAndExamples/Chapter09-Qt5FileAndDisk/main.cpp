#include "mainwindow.h"
#include "QFileTest.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //OpenFileWithQFile();
    //OpenFileWithQTextStream();

    SaveFileWithQDataStream();
    OpenFileWithQDataStream();

    return a.exec();
}
