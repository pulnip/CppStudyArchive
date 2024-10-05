#include <cmath>
#include "fwd.hpp"

using namespace std;
using namespace cv;
using namespace cvtest;
using namespace cvtest::geometry_transformation;

Mat geometry_transformation::resize_grayscale(const Mat& src,
    const int x_size, const int y_size,
    interpolation::interpolate_grayscale_t itpl
){
    Mat dst(y_size, x_size, CV_8UC1);

    const float y_scale=static_cast<float>(src.rows) / y_size;
    const float x_scale=static_cast<float>(src.cols) / x_size;

    for(int i=0; i<y_size; ++i){
        const float y_origin=y_scale*i;

        for(int j=0; j<x_size; ++j){
            const float x_origin=x_scale*j;

            dst.at<uint8_t>(i, j)=itpl(src, x_origin, y_origin);
        }
    }

    return dst;
}

Mat geometry_transformation::flipX_grayscale(const Mat& src){
    auto dst=Mat(src.size(), CV_8UC1);

    for(int i=0; i<src.rows; ++i){
        int idx=src.cols*i;

        for(int j=0; j<src.cols; ++j)
            dst.data[idx + j]=src.data[idx + src.cols-1 - j];
    }

    return dst;
}
Mat geometry_transformation::flipX(const Mat& src){
    auto dst=Mat(src.size(), CV_8UC3);

    for(int i=0; i<src.rows; ++i){
        int idx=3*src.cols*i;

        for(int j=0; j<src.cols; ++j){
            int offset=3*j;
            int rev=3*(src.cols-1 - j);
            dst.data[idx + offset + 0]=src.data[idx + rev + 0];
            dst.data[idx + offset + 1]=src.data[idx + rev + 1];
            dst.data[idx + offset + 2]=src.data[idx + rev + 2];
        }
    }

    return dst;
}

Mat geometry_transformation::flipY_grayscale(const Mat& src){
    auto dst=Mat(src.size(), CV_8UC1);

    for(int i=0; i<src.rows; ++i){
        int idx=src.cols*i;
        int rev=src.cols*(src.rows-1 - i);

        for(int j=0; j<src.cols; ++j)
            dst.data[idx + j]=src.data[rev + j];
    }

    return dst;
}
Mat geometry_transformation::flipY(const Mat& src){
    auto dst=Mat(src.size(), CV_8UC3);

    for(int i=0; i<src.rows; ++i){
        int idx=3*src.cols*i;
        int rev=3*src.cols*(src.rows-1 - i);

        for(int j=0; j<src.cols; ++j){
            int offset=3*j;
            dst.data[idx + offset + 0]=src.data[rev + offset + 0];
            dst.data[idx + offset + 1]=src.data[rev + offset + 1];
            dst.data[idx + offset + 2]=src.data[rev + offset + 2];
        }
    }

    return dst;
}

Mat geometry_transformation::rotate_grayscale(const Mat& src,
    const float radian,
    interpolation::interpolate_grayscale_t itpl
){
    Mat dst(src.rows, src.cols, CV_8UC1);
    const float cos_d=cos(-radian);
    const float sin_d=sin(-radian);
    const float mid_x=dst.cols/2.0f;
    const float mid_y=dst.rows/2.0f;

    for(int i=0; i<dst.rows; ++i){
        const float y_dst=i-mid_y;
        const int index=dst.cols*i;

        for(int j=0; j<dst.cols; ++j){
            const float x_dst=j-mid_x;

            const float x_origin =  cos_d*x_dst + sin_d*y_dst + mid_x;
            const float y_origin = -sin_d*x_dst + cos_d*y_dst + mid_y;

            dst.data[index + j]=itpl(src, x_origin, y_origin);
        }
    }

    return dst;
}
