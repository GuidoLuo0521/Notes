#include <QCoreApplication>

#include "GeneralImageTransforms.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Resize();

//    PyrDown();

    //BuildPyramid();

    //PyrUp();

    //WarpAffine();

    //InPaint();

    //FastNlMeansDenoising();

    HistogramEqualization();

    return a.exec();
}
