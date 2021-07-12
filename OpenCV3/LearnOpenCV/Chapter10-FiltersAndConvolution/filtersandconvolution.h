#ifndef FILTERSANDCONVOLUTION_H
#define FILTERSANDCONVOLUTION_H

#include <opencv2/opencv.hpp>

/*
 * enum BorderTypes {
    BORDER_CONSTANT    = 0, //!< `iiiiii|abcdefgh|iiiiiii`  with some specified `i`
    BORDER_REPLICATE   = 1, //!< `aaaaaa|abcdefgh|hhhhhhh`
    BORDER_REFLECT     = 2, //!< `fedcba|abcdefgh|hgfedcb`
    BORDER_WRAP        = 3, //!< `cdefgh|abcdefgh|abcdefg`
    BORDER_REFLECT_101 = 4, //!< `gfedcb|abcdefgh|gfedcba`
    BORDER_TRANSPARENT = 5, //!< `uvwxyz|abcdefgh|ijklmno`

    BORDER_REFLECT101  = BORDER_REFLECT_101, //!< same as BORDER_REFLECT_101
    BORDER_DEFAULT     = BORDER_REFLECT_101, //!< same as BORDER_REFLECT_101
    BORDER_ISOLATED    = 16 //!< do not look outside of ROI
};
*/

cv::Mat MakeBorder( const char* szPath, const cv::BorderTypes bt)
{
    cv::Mat mat = cv::imread(szPath);
    cv::copyMakeBorder( mat, mat, 5,5,5,5, bt );
    return mat;
}


/*
 * enum ThresholdTypes {
    THRESH_BINARY     = 0, //!< \f[\texttt{dst} (x,y) =  \fork{\texttt{maxval}}{if \(\texttt{src}(x,y) > \texttt{thresh}\)}{0}{otherwise}\f]
    THRESH_BINARY_INV = 1, //!< \f[\texttt{dst} (x,y) =  \fork{0}{if \(\texttt{src}(x,y) > \texttt{thresh}\)}{\texttt{maxval}}{otherwise}\f]
    THRESH_TRUNC      = 2, //!< \f[\texttt{dst} (x,y) =  \fork{\texttt{threshold}}{if \(\texttt{src}(x,y) > \texttt{thresh}\)}{\texttt{src}(x,y)}{otherwise}\f]
    THRESH_TOZERO     = 3, //!< \f[\texttt{dst} (x,y) =  \fork{\texttt{src}(x,y)}{if \(\texttt{src}(x,y) > \texttt{thresh}\)}{0}{otherwise}\f]
    THRESH_TOZERO_INV = 4, //!< \f[\texttt{dst} (x,y) =  \fork{0}{if \(\texttt{src}(x,y) > \texttt{thresh}\)}{\texttt{src}(x,y)}{otherwise}\f]
    THRESH_MASK       = 7,
    THRESH_OTSU       = 8, //!< flag, use Otsu algorithm to choose the optimal threshold value
    THRESH_TRIANGLE   = 16 //!< flag, use Triangle algorithm to choose the optimal threshold value
};
*/

cv::Mat Threshold(const char* szPath, double thre, double max ,cv::ThresholdTypes tt)
{
    cv::Mat mat = cv::imread(szPath, cv::IMREAD_GRAYSCALE);

    cv::threshold(mat, mat, thre, max, tt);

    return mat;
}


/*
 * adaptiveMethod：
 * ADAPTIVE_THRESH_MEAN_C的计算方法是计算出领域的平均值再减去第七个参数double C的值。
 * ADAPTIVE_THRESH_GAUSSIAN_C的计算方法是计算出领域的高斯均值再减去第七个参数double C的值。
 *
 * thresholdType：
 * THRESH_BINARY 和THRESH_BINARY_INV
*/

cv::Mat AdaptiveThreshold(const char* szPath, double max, int adaptiveMethod, int thresholdType, int blockSize, double c)
{
    cv::Mat mat = cv::imread(szPath, cv::IMREAD_GRAYSCALE);
    cv::adaptiveThreshold(mat, mat, max, adaptiveMethod, thresholdType, blockSize, c);
    return mat;
}




#endif // FILTERSANDCONVOLUTION_H
