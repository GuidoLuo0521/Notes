#include "mainwindow.h"
#include "webexplorer.h"
#include "downloadwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //WebExplorer w;
    DownLoadWindow w;
    w.show();
    return a.exec();
}
