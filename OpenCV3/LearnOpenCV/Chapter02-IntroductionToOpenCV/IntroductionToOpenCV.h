#ifndef DISPLAYPICTURE_H
#define DISPLAYPICTURE_H

#include <opencv2/opencv.hpp>

///
/// \brief DisplayPicture
///
void DisplayPicture(const char* szPath)
{
    cv::Mat mat = cv::imread(szPath);

    if( mat.empty() )
        return;

    cv::imshow(szPath, mat);
}


void PlayVideo( const char* szPath )
{
    cv::VideoCapture cap;
    cap.open(szPath);


    cv::Mat frame;
    for(; ; )
    {
        cap >> frame;
        if( frame.empty() )
            continue;

        cv::imshow(szPath, frame);

        // 等待 33ms 没按键开始下一帧
        if(cv::waitKey(33) >= 0)
            break;

    }
}



#endif // DISPLAYPICTURE_H

