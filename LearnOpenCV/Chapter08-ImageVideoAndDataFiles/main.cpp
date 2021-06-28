#include <QCoreApplication>

#include "imagevideoanddatafiles.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const char* szPath = "../lena.jpg";
    const char* szExt = ".png";

    std::vector<uchar> vData = Compression(szPath, szExt);
    cv::Mat mat= Decompression(vData);

    cv::imshow(szPath, mat);


    return a.exec();
}
