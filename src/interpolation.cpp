#include <cmath>
#include "fwd.hpp"

using namespace std;
using namespace cv;
using namespace cvtest;
using namespace cvtest::interpolation;

pixel interpolation::replicate_grayscale(const Mat& src,
    const float x, const float y
){
    if(isMatOutside(src, x, y))
        return BLACK;

    const int repl_x=max(static_cast<int>(x), 0);
    const int repl_y=max(static_cast<int>(y), 0);

    return src.at<uint8_t>(repl_y, repl_x);
}

pixel interpolation::nearest_grayscale(const Mat& src,
    const float x, const float y
){
    if(isMatOutside(src, x, y))
        return BLACK;

    const int near_x=clip(static_cast<int>(x+0.5f), 0, src.cols-1);
    const int near_y=clip(static_cast<int>(y+0.5f), 0, src.rows-1);

    return src.at<uint8_t>(near_y, near_x);
}

pixel interpolation::bilinear_grayscale(const Mat& src,
    const float x, const float y
){
    if(isMatOutside(src, x, y))
        return BLACK;

    const int x0=max(static_cast<int>(x), 0);
    const int x1=min(static_cast<int>(x0+1), src.cols-1);
    const int y0=max(static_cast<int>(y), 0);
    const int y1=min(static_cast<int>(y0+1), src.rows-1);

    const uint8_t y0x0=src.data[src.cols*y0 + x0];
    const uint8_t y0x1=src.data[src.cols*y0 + x1];
    const uint8_t y1x0=src.data[src.cols*y1 + x0];
    const uint8_t y1x1=src.data[src.cols*y1 + x1];

    const float len_x0=x-x0;
    const float len_x1=1-len_x0;
    const float len_y0=y-y0;
    const float len_y1=1-len_y0;

    const float weight_y0x0=len_y0*len_x0;
    const float weight_y0x1=len_y0*len_x1;
    const float weight_y1x0=len_y1*len_x0;
    const float weight_y1x1=len_y1*len_x1;

    // return weight_y0x0*y0x0 + weight_y0x1*y0x1 +
    //     weight_y1x0*y1x0 + weight_y1x1*y1x1;

    return weight_y1x1*y0x0 + weight_y1x0*y0x1 +
        weight_y0x1*y1x0 + weight_y0x0*y1x1;
}

static uint8_t cubic(const float dx,
    const uint8_t fx_1, const uint8_t fx0, const uint8_t fx1, const uint8_t fx2
){
    Mat v=(Mat_<float>(1, 4)<<dx*dx*dx, dx*dx, dx, 1);
    static Mat inv=(Mat_<float>(4, 4)<<
        -1.0f/6,  0.5f, -0.5f,  1.0f/6,
         0.5f  , -1.0f,  0.5f,  0.0f  ,
        -1.0f/3, -0.5f,  1.0f, -1.0f/6,
         0.0f  ,  1.0f,  0.0f,  0.0f
    );
    Mat fx=(Mat_<float>(4, 1)<<fx_1, fx0, fx1, fx2);

    return Mat(v*inv*fx).at<float>(0, 0);
}

static uint8_t cubic_x_grayscale(const Mat& src, const float x, const int y){
    if(isMatOutside(src, x, y))
        return BLACK;

    const auto fx_1=src.at<uint8_t>(y, max<int>(  0,        x-1));
    const auto fx0 =src.at<uint8_t>(y, max<int>(  0,        x+0));
    const auto fx1 =src.at<uint8_t>(y, min<int>(x+1, src.cols-1));
    const auto fx2 =src.at<uint8_t>(y, min<int>(x+2, src.cols-1));

    return cubic(x-floor(x), fx_1, fx0, fx1, fx2);
}

uint8_t interpolation::bicubic_grayscale(const Mat& src,
    const float x, const float y
){
    if(isMatOutside(src, x, y))
        return BLACK;

    const auto fy_1=cubic_x_grayscale(src, x, max<int>(  0,        y-1));
    const auto fy0 =cubic_x_grayscale(src, x, max<int>(  0,        y+0));
    const auto fy1 =cubic_x_grayscale(src, x, min<int>(y+1, src.rows-1));
    const auto fy2 =cubic_x_grayscale(src, x, min<int>(y+2, src.rows-1));

    return cubic(y-floor(y), fy_1, fy0, fy1, fy2);
}
