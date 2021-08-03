#include "mainwindow.h"

#include <QApplication>

#include "producerthread.h"
#include "customthread.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

  //  MainWindow w;
   // w.show();

    ProducerThread producer;
    CustomThread customer0;
    CustomThread customer1;
    CustomThread customer2;

    producer.start();
    customer0.start();
    customer1.start();
    customer2.start();

    producer.wait();
    customer0.wait();
    customer1.wait();
    customer2.wait();

    return a.exec();
}
