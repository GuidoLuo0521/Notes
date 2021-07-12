#ifndef IMAGEVIDEOANDDATAFILES_H
#define IMAGEVIDEOANDDATAFILES_H

#include <opencv2/opencv.hpp>


cv::Mat ReadingFiles(const char* szPath)
{
    return cv::imread(szPath);
}

std::vector<uchar> Compression(const char* szPath, const char* szExt)
{
    cv::Mat mat = ReadingFiles(szPath);

    //encode image
    std::vector<uchar> vEncode;
    cv::imencode(szExt, mat, vEncode);

    return vEncode;
}

cv::Mat Decompression(std::vector<uchar> vData)
{
    return cv::imdecode(vData,  cv::IMREAD_COLOR);
}


#endif // IMAGEVIDEOANDDATAFILES_H
