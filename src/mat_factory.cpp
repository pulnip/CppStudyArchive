#include "fwd.hpp"

using namespace cv;
using namespace cvtest;
using namespace cvtest::factory;

Mat factory::simpleImage_grayscale(const Size& size, pixel color){
    auto dst=Mat(size, CV_8UC1);

    for(int i=0; i<dst.rows*dst.cols; ++i)
        dst.data[i]=color;

    return dst;
}

Mat factory::simpleImage(const Size& size,
    pixel r, pixel g, pixel b
){
    auto dst=Mat(size, CV_8UC3);

    for(int i=0; i<dst.rows*dst.cols; ++i){
        dst.data[3*i + 0]=r;
        dst.data[3*i + 1]=g;
        dst.data[3*i + 2]=b;
    }

    return dst;
}
