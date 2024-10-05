#include "fwd.hpp"

using namespace cv;
using namespace cvtest::image_analyzer;

Mat cvtest::image_transformation::equalizeHistogram_grayscale(const Mat& src){
    Mat dst=src.clone();
    CDF src_cdf(dst);

    for(int i=0; i<dst.rows*dst.cols; ++i)
        dst.data[i]=255*src_cdf.cd_normal(dst.data[i]);

    return dst;
}
