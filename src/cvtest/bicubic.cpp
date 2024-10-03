#define _USE_MATH_DEFINES
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define nameof(x) (#x)
#define matshow(x) (imshow(nameof(x), x))

constexpr uint8_t BLACK=0x00;

inline bool isMatOutside(const Mat& src, const float x, const float y){
    return (x < 0) || (src.cols <= x) || (y < 0) || (src.rows <= y);
}

uint8_t cubic(const float dx,
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

uint8_t cubic_x(const Mat& src, const float x, const int y){
    if(isMatOutside(src, x, y))
        return BLACK;

    const auto fx_1=src.at<uint8_t>(y, max<int>(  0,        x-1));
    const auto fx0 =src.at<uint8_t>(y, max<int>(  0,        x+0));
    const auto fx1 =src.at<uint8_t>(y, min<int>(x+1, src.cols-1));
    const auto fx2 =src.at<uint8_t>(y, min<int>(x+2, src.cols-1));

    return cubic(x-floor(x), fx_1, fx0, fx1, fx2);
}

uint8_t bicubic(const Mat& src, const float x, const float y){
    if(isMatOutside(src, x, y))
        return BLACK;

    const auto fy_1=cubic_x(src, x, max<int>(  0,        y-1));
    const auto fy0 =cubic_x(src, x, max<int>(  0,        y+0));
    const auto fy1 =cubic_x(src, x, min<int>(y+1, src.rows-1));
    const auto fy2 =cubic_x(src, x, min<int>(y+2, src.rows-1));

    return cubic(y-floor(y), fy_1, fy0, fy1, fy2);
}

Mat resize(const Mat& src, const int x_size, const int y_size,
    uint8_t (*interpolate)(const Mat&, float, float)
){
    Mat dst(y_size, x_size, CV_8UC1);

    const float y_scale=static_cast<float>(src.rows) / y_size;
    const float x_scale=static_cast<float>(src.cols) / x_size;

    for(int i=0; i<y_size; ++i){
        const float y_origin=y_scale*i;

        for(int j=0; j<x_size; ++j){
            const float x_origin=x_scale*j;

            dst.at<uint8_t>(i, j)=interpolate(src, x_origin, y_origin);
        }
    }

    return dst;
}

int main(void){
	Mat source=imread("Lena_256x256.png", IMREAD_GRAYSCALE);
    matshow(source);

    Mat resized=resize(source, 512, 512, bicubic);
    matshow(resized);

	waitKey(0);
	return 0;
}

#undef _USE_MATH_DEFINES
#undef nameof
#undef matshow
