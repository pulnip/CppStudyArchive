#include <cmath>
#include "fwd.hpp"

using namespace cv;
using namespace cvtest;
using namespace cvtest::image_transformation;

Mat image_transformation::transform_grayscale(const Mat& src,
    pixelwise_transform_grayscale_t f
){
    Mat dst=src.clone();

    for(int i=0; i<dst.rows*dst.cols; ++i)
        dst.data[i]=f(dst.data[i]);

    return dst;
}
Mat image_transformation::transform(const Mat& src,
    pixelwise_transform_grayscale_t f
){
    Mat dst=src.clone();

    for(int i=0; i<dst.rows*dst.cols; ++i){
        dst.data[3*i + 0]=f(dst.data[3*i + 0]);
        dst.data[3*i + 1]=f(dst.data[3*i + 1]);
        dst.data[3*i + 2]=f(dst.data[3*i + 2]);
    }

    return dst;
}

pixel image_transformation::neg(pixel r){ return 255-r; }
pixel image_transformation::half_black(pixel r){ return r>>1; }
pixel image_transformation::half_white(pixel r){ return (r>>1) + 128; }

Mat image_transformation::transform_grayscale(const Mat& lhs, const Mat& rhs,
    bipixel_transform_grayscale_t f
){
    auto dst=Mat(lhs.size(), CV_8UC1);

    for(int i=0; i<dst.rows*dst.cols; ++i)
        dst.data[i]=f(lhs.data[i], rhs.data[i]);

    return dst;
}
Mat image_transformation::transform(const Mat& lhs, const Mat& rhs,
    bipixel_transform_grayscale_t f
){
    auto dst=Mat(lhs.size(), CV_8UC3);

    for(int i=0; i<dst.rows*dst.cols; ++i){
        dst.data[3*i + 0]=f(lhs.data[3*i + 0], rhs.data[3*i + 0]);
        dst.data[3*i + 1]=f(lhs.data[3*i + 1], rhs.data[3*i + 1]);
        dst.data[3*i + 2]=f(lhs.data[3*i + 2], rhs.data[3*i + 2]);
    }

    return dst;
}

pixel sum(pixel lhs, pixel rhs){ return clip<int>(lhs+rhs, 0x00, 0xff); }
pixel average(pixel lhs, pixel rhs){ return (lhs+rhs)>>1; }
pixel subtract(pixel lhs, pixel rhs){ return clip<int>(lhs-rhs, 0x00, 0xff); }

Mat image_transformation::gamma_grayscale(const Mat& src, float gamma){
    Mat dst=src.clone();

    for(int i=0; i<dst.rows*dst.cols; ++i)
        dst.data[i]=255 * std::pow(dst.data[i]/255.0f, gamma);

    return dst;
}

