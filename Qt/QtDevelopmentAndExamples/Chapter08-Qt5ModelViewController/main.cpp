#include "mainwindow.h"
#include "dirmodeex.h"
#include "histogramform.h"
#include "delegateview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //DirModeEx w;
    //HistogramForm w;
    DelegateView w;
    w.show();
    return a.exec();
}
