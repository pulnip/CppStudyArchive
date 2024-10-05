#include "fwd.hpp"

using namespace cv;
using namespace cvtest::image_analyzer;

static inline uint8_t match(uint8_t l, const CDF& origin, const CDF& spec){
    return spec.inv(origin.cd_normal(l));
}

Mat cvtest::image_transformation::matchHistogram_grayscale(const Mat& src,
    const CDF& hist
){
    Mat dst=src.clone();
    CDF src_cdf(dst);

    for(int i=0; i<dst.rows*dst.cols; ++i){
        dst.data[i]=match(dst.data[i], src_cdf, hist);
    }

    return dst;
}
