#ifndef GENERALIMAGETRANSFORMS_H
#define GENERALIMAGETRANSFORMS_H

#include <opencv2/opencv.hpp>

#include <QString>

using namespace cv;

/*
 void cv::resize(
        cv::InputArray src, // Input image
        cv::OutputArray dst, // Result image
        cv::Size dsize, // New size
        double fx = 0, // x-rescale
        double fy = 0, // y-rescale
        int interpolation = CV::INTER_LINEAR // interpolation method
);

cv::INTER_NEAREST Nearest neighbor
cv::INTER_LINEAR Bilinear
cv::INTER_AREA Pixel area resampling
cv::INTER_CUBIC Bicubic interpolation
cv::INTER_LANCZOS4 Lanczos interpolation over 8 × 8 neighborhood

*/

void Resize()
{
    Mat src = imread("f:/ecg.jpg"), dst;
    imshow("raw", src);

    resize(src, dst, cv::Size(200, 200), 0, 0, cv::INTER_NEAREST);
    imshow("INTER_NEAREST", dst);

    resize(src, dst, cv::Size(200, 200), 0, 0,  cv::INTER_LINEAR);
    imshow("INTER_LINEAR", dst);

    resize(src, dst, cv::Size(200, 200), 0, 0, cv::INTER_AREA);
    imshow("INTER_AREA", dst);

    resize(src, dst, cv::Size(200, 200), 0, 0, cv::INTER_CUBIC);
    imshow("INTER_CUBIC", dst);

    resize(src, dst, cv::Size(200, 200), 0, 0, cv::INTER_LANCZOS4);
    imshow("INTER_LANCZOS4", dst);

}


/*
 * void cv::pyrDown(
            cv::InputArray src, // Input image
            cv::OutputArray dst, // Result image
            const cv::Size& dstsize = cv::Size() // Output image size
        );
*/
void PyrDown()
{
    Mat src = imread("f:/ecg.jpg"), dst;
    imshow("raw", src);

    cv::pyrDown(src, dst);
    imshow("PyrDown", dst);

}

/*
void cv::buildPyramid(
    cv::InputArray src, // Input image
    cv::OutputArrayOfArrays dst, // Output images from pyramid
    int maxlevel // Number of pyramid levels
);

*/
void BuildPyramid()
{
    Mat src = imread("f:/ecg.jpg"), dst;
    imshow("raw", src);

    int nMax = 5;

    std::vector<Mat> vDst;
    cv::buildPyramid(src, vDst, nMax);

    for (int i = 0 ; i < vDst.size(); ++i)
    {
        Mat& dst = vDst[i];
        QString strTitle = QString("BuildPyramid - %1").arg(i);
        imshow(strTitle.toLocal8Bit().data(), dst);
    }
}


/*
void cv::pyrUp(
    cv::InputArray src, // Input image
    cv::OutputArray dst, // Result image
    const cv::Size& dstsize = cv::Size() // Output image size
);
*/
void PyrUp()
{
    Mat src = imread("f:/ecg.jpg"), dst;
    imshow("raw", src);

    cv::pyrUp(src, dst);
    imshow("PyrUp", dst);

}

/*
 * void cv::warpAffine(
            cv::InputArray src, // Input image
            cv::OutputArray dst, // Result image
            cv::InputArray M, // 2-by-3 transform mtx
            cv::Size dsize, // Destination image size
            int flags = cv::INTER_LINEAR, // Interpolation, inverse
            int borderMode = cv::BORDER_CONSTANT, // Pixel extrapolation
            const cv::Scalar& borderValue = cv::Scalar() // For constant borders
);


cv::Mat cv::getRotationMatrix2D( // Return 2-by-3 matrix
        cv::Point2f center // Center of rotation
        double angle, // Angle of rotation
        double scale // Rescale after rotation
);
*/
void WarpAffine()
{
    Mat src = imread("f:/lena.jpg"), dst;
    imshow("raw", src);

    Point2f srcTri[3];
    Point2f dstTri[3];
    //设置三个点来计算仿射变换
    srcTri[0] = Point2f(0, 0);
    srcTri[1] = Point2f(src.cols - 1, 0);
    srcTri[2] = Point2f(0, src.rows - 1);

    dstTri[0] = Point2f(src.cols*0.0, src.rows*0.33);
    dstTri[1] = Point2f(src.cols*0.35, src.rows*0.25);
    dstTri[2] = Point2f(src.cols*0.15, src.rows*0.7);

    cv::Mat mat = getAffineTransform(srcTri, dstTri);

    cv::warpAffine(src, dst, mat, dst.size());
    imshow("getAffineTransform", dst);


    cv::Point2f center =cv::Point2f( dst.cols / 2, dst.rows / 2);
    // 逆时针
    cv::Mat rotmat = getRotationMatrix2D(center, 10, 0.5);
    cv::warpAffine(src, dst, rotmat, dst.size());
    imshow("getRotationMatrix2D", dst);

}

/*
 * void cv::inpaint(
        cv::InputArray src,         // Input image: 8-bit, 1 or 3 channels
        cv::InputArray inpaintMask, // 8-bit, 1 channel. Inpaint nonzeros
        cv::OutputArray dst,        // Result image
        double inpaintRadius,       // Range to consider around pixel
        int flags                   // Select NS or TELEA
);
// flags Inpainting method that could be cv::INPAINT_NS or cv::INPAINT_TELEA
*/
void InPaint()
{
    Mat src = imread("f:/lena-inpaint.jpg"), dst;
    imshow("raw", src);

    Mat mask = imread("f:/lena-inpaint.jpg", IMREAD_GRAYSCALE);
    cv::threshold(mask, mask, 20, 255, THRESH_BINARY_INV);

    Mat kernel = getStructuringElement(MORPH_ELLIPSE, cv::Size(7, 7));
    morphologyEx(mask, mask, MORPH_DILATE, kernel);

    imshow("Mask", mask);

    cv::inpaint(src, mask, dst, 5, INPAINT_NS);
    imshow("INPAINT_NS", dst);

    cv::inpaint(src, mask, dst, 5, INPAINT_TELEA);
    imshow("INPAINT_TELEA", dst);
}

void FastNlMeansDenoising()
{
    Mat src = imread("f:/dwk.jpg"), dst;
    imshow("src", src);

    cv::fastNlMeansDenoisingColored(src, dst);
    imshow("dst", dst);
}

void HistogramEqualization()
{
    // must be cv::8U
    Mat src = imread("f:/dwk.jpg", IMREAD_GRAYSCALE), dst;
    imshow("src", src);

    cv::equalizeHist(src, dst);
    imshow("dst1", dst);

    cv::equalizeHist(dst, dst);
    imshow("dst2", dst);

}


#endif // GENERALIMAGETRANSFORMS_H
