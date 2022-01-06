#include "mainwindow.h"
#include "rasterwindow.h"

#include <QApplication>
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    RasterWindow w;
    w.show();

    return a.exec();
}
