#include <QCoreApplication>

#include <iostream>
#include <QMutex>
#include <QMutexLocker>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //QMutexLocker

    return a.exec();
}
