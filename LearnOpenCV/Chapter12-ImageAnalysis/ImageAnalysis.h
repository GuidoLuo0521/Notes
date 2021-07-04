#ifndef IMAGEANALYSIS_H
#define IMAGEANALYSIS_H

#include <opencv2/opencv.hpp>


/*
第一个参数，InputArray类型的image，输入图像，即源图像，需为8位的单通道二进制图像，可以将任意的源图载入进来后由函数修改成此格式后，再填在这里。
第二个参数，InputArray类型的lines，经过调用HoughLines函数后储存了霍夫线变换检测到线条的输出矢量。每一条线由具有两个元素的矢量表示，其中，是离坐标原点((0,0)（也就是图像的左上角）的距离。 是弧度线条旋转角度（0~垂直线，π/2~水平线）。
第三个参数，double类型的rho，以像素为单位的距离精度。另一种形容方式是直线搜索时的进步尺寸的单位半径。PS:Latex中/rho就表示 。
第四个参数，double类型的theta，以弧度为单位的角度精度。另一种形容方式是直线搜索时的进步尺寸的单位角度。
第五个参数，int类型的threshold，累加平面的阈值参数，即识别某部分为图中的一条直线时它在累加平面中必须达到的值。大于阈值threshold的线段才可以被检测通过并返回到结果中。
第六个参数，double类型的srn，有默认值0。对于多尺度的霍夫变换，这是第三个参数进步尺寸rho的除数距离。粗略的累加器进步尺寸直接是第三个参数rho，而精确的累加器进步尺寸为rho/srn。
第七个参数，double类型的stn，有默认值0，对于多尺度霍夫变换，srn表示第四个参数进步尺寸的单位角度theta的除数距离。且如果srn和stn同时为0，就表示使用经典的霍夫变换。否则，这两个参数应该都为正数。
*/
void HoughLines()
{
    cv::Mat src = cv::imread("d:/TestImages/houghline.png"), mid, dst;
    //imshow("raw", src);

    // 并进行边缘检测
    cv::Canny(src, dst, 150, 200);
    //imshow("Canny", dst);

    //
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(dst, lines, 1, CV_PI / 180.0, 150);

    //
    for(int i = 0; i < lines.size(); ++i)
    {
        float rho = lines[i][0], theta = lines[i][1];
        cv::Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 100*(-b));
        pt1.y = cvRound(y0 + 100*(a));
        pt2.x = cvRound(x0 - 100*(-b));
        pt2.y = cvRound(y0 - 100*(a));
        cv::line( src, pt1, pt2, cv::Scalar(0,0,255), 1, cv::LINE_AA);
    }

    //
    cv::imshow("line", src);

}


/*
第一个参数，InputArray类型的image，输入图像，即源图像，需为8位的单通道二进制图像，可以将任意的源图载入进来后由函数修改成此格式后，再填在这里。
第二个参数，InputArray类型的lines，经过调用HoughLinesP函数后后存储了检测到的线条的输出矢量，每一条线由具有四个元素的矢量(x_1,y_1, x_2, y_2）  表示，其中，(x_1, y_1)和(x_2, y_2) 是是每个检测到的线段的结束点。
第三个参数，double类型的rho，以像素为单位的距离精度。另一种形容方式是直线搜索时的进步尺寸的单位半径。
第四个参数，double类型的theta，以弧度为单位的角度精度。另一种形容方式是直线搜索时的进步尺寸的单位角度。
第五个参数，int类型的threshold，累加平面的阈值参数，即识别某部分为图中的一条直线时它在累加平面中必须达到的值。大于阈值threshold的线段才可以被检测通过并返回到结果中。
第六个参数，double类型的minLineLength，有默认值0，表示最低线段的长度，比这个设定参数短的线段就不能被显现出来。
第七个参数，double类型的maxLineGap，有默认值0，允许将同一行点与点之间连接起来的最大的距离。
*/
void HoughLinesP()
{
    cv::Mat src = cv::imread("d:/TestImages/houghline.png"), mid, dst;
    //imshow("raw", src);

    // 并进行边缘检测
    cv::Canny(src, dst, 50, 150);
    imshow("Canny", dst);

    //
    std::vector<cv::Vec4f> lines;
    cv::HoughLinesP(dst, lines, 5, CV_PI / 180.0, 100, 80);

    //
    for(int i = 0; i < lines.size(); ++i)
    {
        cv::Vec4i l = lines[i];
        cv::line( src, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 1, cv::LINE_AA);
    }

    //
    cv::imshow("line", src);

}


/*
第一个参数，InputArray类型的image，输入图像，即源图像，需为8位的灰度单通道图像。
第二个参数，InputArray类型的circles，经过调用HoughCircles函数后此参数存储了检测到的圆的输出矢量，每个矢量由包含了3个元素的浮点矢量(x, y, radius)表示。
第三个参数，int类型的method，即使用的检测方法，目前OpenCV中就霍夫梯度法一种可以使用，它的标识符为CV_HOUGH_GRADIENT，在此参数处填这个标识符即可。
第四个参数，double类型的dp，用来检测圆心的累加器图像的分辨率于输入图像之比的倒数，且此参数允许创建一个比输入图像分辨率低的累加器。上述文字不好理解的话，来看例子吧。例如，如果dp= 1时，累加器和输入图像具有相同的分辨率。如果dp=2，累加器便有输入图像一半那么大的宽度和高度。
第五个参数，double类型的minDist，为霍夫变换检测到的圆的圆心之间的最小距离，即让我们的算法能明显区分的两个不同圆之间的最小距离。这个参数如果太小的话，多个相邻的圆可能被错误地检测成了一个重合的圆。反之，这个参数设置太大的话，某些圆就不能被检测出来了。
第六个参数，double类型的param1，有默认值100。它是第三个参数method设置的检测方法的对应的参数。对当前唯一的方法霍夫梯度法CV_HOUGH_GRADIENT，它表示传递给canny边缘检测算子的高阈值，而低阈值为高阈值的一半。
第七个参数，double类型的param2，也有默认值100。它是第三个参数method设置的检测方法的对应的参数。对当前唯一的方法霍夫梯度法CV_HOUGH_GRADIENT，它表示在检测阶段圆心的累加器阈值。它越小的话，就可以检测到更多根本不存在的圆，而它越大的话，能通过检测的圆就更加接近完美的圆形了。
第八个参数，int类型的minRadius,有默认值0，表示圆半径的最小值。
第九个参数，int类型的maxRadius,也有默认值0，表示圆半径的最大值。
*/
void HoughCircles()
{
    cv::Mat src = cv::imread("d:/TestImages/circle.png"), mid, dst;
    //imshow("raw", src);

    //【3】转为灰度图，进行图像平滑
    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);//转化边缘检测后的图为灰度图
    cv::GaussianBlur( dst, dst, cv::Size(9, 9), 2, 2 );
    cv::imshow("GaussianBlur", dst);

    //
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles( dst, circles, cv::HOUGH_GRADIENT,1.5, 10, 200, 100, 0, 0 );

    //
    for(int i = 0; i < circles.size(); ++i)
    {
        cv::Point center(cvRound( circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound( circles[i][2]);
        //绘制圆心
        cv::circle( src, center, 1, cv::Scalar( 0, 255, 0), -1, 8, 0 );
        //绘制圆轮廓
        cv::circle( src, center, radius, cv::Scalar(0, 0, 255), 1, 8, 0 );
    }

    //
    cv::imshow("circles", src);

}





#endif // IMAGEANALYSIS_H
