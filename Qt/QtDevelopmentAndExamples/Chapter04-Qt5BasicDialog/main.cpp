#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen screen(QPixmap("d:\\d7f82e12762a65d9164a53bcc960e9b6.jpg"));

    screen.show();

    a.processEvents();

    MainWindow w;
    w.show();

    screen.finish(&w);

    return a.exec();
}
