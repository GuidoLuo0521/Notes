#ifndef EXERCISES_H
#define EXERCISES_H

#include <opencv2/opencv.hpp>

using namespace cv;

/*
 * 1. Load an image with interesting textures. Smooth the image in several ways using
    cv::smooth() with smoothtype=cv::GAUSSIAN.
        a. Use a symmetric 3 × 3, 5 × 5, 9 × 9, and 11 × 11 smoothing window size and display the results.
        b. Are the output results nearly the same by smoothing
            the image twice with a 5 × 5 Gaussian filter as when you smooth once with two 11 × 11 filters?
            Why or why not?

    这玩意，不是坑人么？ version3 好像没了

smoothing:

低通滤波器：
void cv::blur(
    cv::InputArray src, // Input image
    cv::OutputArray dst, // Result image
    cv::Size ksize, // Kernel size
    cv::Point anchor = cv::Point(-1,-1), // Location of anchor point
    int borderType = cv::BORDER_DEFAULT // Border extrapolation to use
    );

方波滤波器：
void cv::boxFilter(
    cv::InputArray src, // Input image
    cv::OutputArray dst, // Result image
    int ddepth, // Output depth (e.g., CV_8U)
    cv::Size ksize, // Kernel size
    cv::Point anchor = cv::Point(-1,-1), // Location of anchor point
    bool normalize = true, // If true, divide by box area  表示内核是否其区域归一化。
    int borderType = cv::BORDER_DEFAULT // Border extrapolation to use
    );

高斯滤波器：
void cv::GaussianBlur(
    cv::InputArray src, // Input image
    cv::OutputArray dst, // Result image
    cv::Size ksize, // Kernel size
    double sigmaX, // Gaussian half-width in x-direction
    double sigmaY = 0.0, // Gaussian half-width in y-direction
    int borderType = cv::BORDER_DEFAULT // Border extrapolation to use
);

双边滤波器
void cv::bilateralFilter(
    cv::InputArray src, // Input image
    cv::OutputArray dst, // Result image
    int d, // Pixel neighborhood size (max distance)
    double sigmaColor, // Width param for color weight function
    double sigmaSpace, // Width param for spatial weight function
    int borderType = cv::BORDER_DEFAULT // Border extrapolation to use
    );

*/

void Exercises_1()
{

    Mat src = imread("f:/ecg.jpg"), dst;
    cv::resize(src, src, cv::Size(200,200));

    GaussianBlur(src, dst, cv::Size(3,3), 2 );
    imshow("3*3", dst);

    GaussianBlur(src, dst, cv::Size(5,5), 2 );
    imshow("5*5", dst);

    GaussianBlur(src, dst, cv::Size(7,7), 2 );
    imshow("7*7", dst);

    GaussianBlur(src, dst, cv::Size(9,9), 2 );
    imshow("9*9", dst);

    GaussianBlur(src, dst, cv::Size(11,11), 2 );
    imshow("11*11", dst);


}



#endif // EXERCISES_H
