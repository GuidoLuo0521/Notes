#include <QCoreApplication>

#include "filtersandconvolution.h"
#include "Exercises.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


///   Threshold
//    const char* szPath = "../lena.jpg";
//    cv::imshow("THRESH_BINARY", Threshold(szPath, 125, 255, cv::THRESH_BINARY));
//    cv::imshow("THRESH_BINARY_INV", Threshold(szPath, 125, 255, cv::THRESH_BINARY_INV));
//    cv::imshow("THRESH_TRUNC", Threshold(szPath, 125, 255, cv::THRESH_TRUNC));
//    cv::imshow("THRESH_TOZERO", Threshold(szPath, 125, 255, cv::THRESH_TOZERO));
//    cv::imshow("THRESH_TOZERO_INV", Threshold(szPath, 125, 255, cv::THRESH_TOZERO_INV));
//    cv::imshow("THRESH_MASK", Threshold(szPath, 125, 255, cv::THRESH_MASK));
//    cv::imshow("THRESH_OTSU", Threshold(szPath, 125, 255, cv::THRESH_OTSU));
//    cv::imshow("THRESH_TRIANGLE", Threshold(szPath, 125, 255, cv::THRESH_TRIANGLE));


///   AdaptiveThreshold
//    const char* szPath = "f:/ad1.png";
//    cv::imshow("raw", cv::imread(szPath, cv::IMREAD_GRAYSCALE));
//    cv::imshow("ADAPTIVE_THRESH_MEAN_C", AdaptiveThreshold(szPath, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 5, 5));
//    cv::imshow("ADAPTIVE_THRESH_GAUSSIAN_C", AdaptiveThreshold(szPath, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 5, 5));


///   Filter

    Exercises_1();


    return a.exec();
}
