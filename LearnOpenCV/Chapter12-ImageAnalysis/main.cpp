#include <QCoreApplication>

#include "ImageAnalysis.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //HoughLines();

    //HoughLinesP();

    HoughCircles();

    return a.exec();
}
