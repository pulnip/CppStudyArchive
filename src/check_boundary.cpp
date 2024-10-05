#include "fwd.hpp"

using namespace cv;
using namespace cvtest;
using namespace cvtest::interpolation;

bool interpolation::isMatOutside(const Mat& src,
    const float x, const float y
){
    return (x < 0) || (src.cols <= x) || (y < 0) || (src.rows <= y);
}
