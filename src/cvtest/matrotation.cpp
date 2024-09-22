#define _USE_MATH_DEFINES
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define nameof(x) (#x)
#define matshow(x) (imshow(nameof(x), x))

namespace interpolation{
    constexpr uint8_t BLACK=0;

    inline bool isMatOutside(const Mat& src, const float x, const float y){
        return (x < 0) || (src.cols <= x) || (y < 0) || (src.rows <= y);
    }
    inline int clip(int x, int m, int M){
        return min(max(x, m), M);
    }

    namespace grayscale{
        inline uint8_t replicate(const Mat& src, const float x, const float y){
            if(isMatOutside(src, x, y))
                return BLACK;

            const int repl_x=max(static_cast<int>(x), 0);
            const int repl_y=max(static_cast<int>(y), 0);

            return src.data[src.cols*repl_y + repl_x];
        }

        inline uint8_t nearest(const Mat& src, const float x, const float y){
            if(isMatOutside(src, x, y))
                return BLACK;

            const int near_x=clip(static_cast<int>(x+0.5f), 0, src.cols-1);
            const int near_y=clip(static_cast<int>(y+0.5f), 0, src.rows-1);

            return src.data[src.cols*near_y + near_x];
        }

        inline uint8_t bilinear(const Mat& src, const float x, const float y){
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

            return weight_y0x0*y0x0 + weight_y0x1*y0x1 +
                weight_y1x0*y1x0 + weight_y1x1*y1x1;
        }
    }
}

namespace transform{
    namespace grayscale{
        inline Mat resize(const Mat& src, const int x_size, const int y_size,
            uint8_t (*interpolate)(const Mat&, float, float)
        ){
            Mat dst(y_size, x_size, CV_8UC1);
            const float y_scale=static_cast<float>(src.rows) / y_size;
            const float x_scale=static_cast<float>(src.cols) / x_size;

            for(int i=0; i<y_size; ++i){
                const float y_origin=y_scale*i;
                const int index=x_size*i;

                for(int j=0; j<x_size; ++j){
                    const float x_origin=x_scale*j;

                    dst.data[index + j]=interpolate(src, x_origin, y_origin);
                }
            }

            return dst;
        }

        inline Mat rotate(const Mat& src, const float degree,
            uint8_t (*interpolate)(const Mat&, float, float)
        ){
            constexpr float DEGREE_TO_RADIAN=M_PI/180;

            Mat dst(src.rows, src.cols, CV_8UC1);
            const float cos_d=cos(-DEGREE_TO_RADIAN*degree);
            const float sin_d=sin(-DEGREE_TO_RADIAN*degree);
            const float mid_x=dst.cols/2.0f;
            const float mid_y=dst.rows/2.0f;

            for(int i=0; i<dst.rows; ++i){
                const float y_dst=i-mid_y;
                const int index=dst.cols*i;

                for(int j=0; j<dst.cols; ++j){
                    const float x_dst=j-mid_x;

                    const float x_origin=cos_d*x_dst - sin_d*y_dst + mid_x;
                    const float y_origin=sin_d*x_dst + cos_d*y_dst + mid_y;

                    dst.data[index + j]=interpolate(src, x_origin, y_origin);
                }
            }

            return dst;
        }
    }
}

int main(void){
    using namespace interpolation::grayscale;
    using namespace transform::grayscale;

	Mat source=imread("Lena_256x256.png", IMREAD_GRAYSCALE);
    matshow(source);

    const int x_newsize=542, y_newsize=542;

    Mat resized_replicate=resize(source, x_newsize, y_newsize, replicate);
    matshow(resized_replicate);
    Mat resized_nearest=resize(source, x_newsize, y_newsize, nearest);
    matshow(resized_nearest);
    Mat resized_bilinear=resize(source, x_newsize, y_newsize, bilinear);
    matshow(resized_bilinear);

    // Mat rotated30=rotate(source, 30, bilinear);
    // matshow(rotated30);
    // Mat rotated45=rotate(source, 45, bilinear);
    // matshow(rotated45);
    // Mat rotated60=rotate(source, 60, bilinear);
    // matshow(rotated60);

	waitKey(0);
	return 0;
}

#undef _USE_MATH_DEFINES
#undef nameof
#undef matshow
