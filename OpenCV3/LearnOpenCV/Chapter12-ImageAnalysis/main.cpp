#include <QCoreApplication>

#include "ImageAnalysis.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //HoughLines();

    //HoughLinesP();

    //HoughCircles();

    FloodFill();

    return a.exec();
}
