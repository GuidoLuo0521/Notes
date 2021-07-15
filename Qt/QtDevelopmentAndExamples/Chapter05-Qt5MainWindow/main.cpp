#include "mainwindow.h"
#include "easyword.h"
#include <QApplication>
#include <QTextCodec>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    EasyWord w;
    w.show();

    return a.exec();
}
