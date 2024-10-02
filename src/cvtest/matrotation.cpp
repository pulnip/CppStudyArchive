#define _USE_MATH_DEFINES
#include <math.h>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <print>
#include <string>

using namespace std;
using namespace cv;

#define nameof(x) (#x)
#define matshow(x) (imshow(nameof(x), x))

class TimeGuard{
    using Clock=chrono::high_resolution_clock;
    using TimePoint=chrono::time_point<Clock>;

    TimePoint start=Clock::now();

  public:
    TimeGuard()=default;
    ~TimeGuard(){
        chrono::duration<double> elapsed{(Clock::now()-start)};
        println("Elapsed: {}", elapsed.count());
    }
};


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

            return weight_y1x1*y0x0 + weight_y1x0*y0x1 +
                weight_y0x1*y1x0 + weight_y0x0*y1x1;
        }

        inline uint8_t bilinear_wrong(const Mat& src, const float x, const float y){
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

        class LagrangeCubic{
            const int x0, x1, x2, x3;
            const uint8_t fx0, fx1, fx2, fx3;
            const float c0, c1, c2, c3;

            float lagrangeConstant(const int xk, uint8_t fxk,
                const uint64_t x0, const uint64_t x1, const uint64_t x2
            ){
                const int dx0=xk-x0;
                const int dx1=xk-x1;
                const int dx2=xk-x2;

                return static_cast<float>(fxk)/(dx0*dx1*dx2);
            }
            
            LagrangeCubic(
                const int x0, const uint8_t fx0,
                const int x1, const uint8_t fx1,
                const int x2, const uint8_t fx2,
                const int x3, const uint8_t fx3)
            : x0(x0), x1(x1), x2(x2), x3(x3)
            , fx0(fx0), fx1(fx1), fx2(fx2), fx3(fx3)
            , c0(lagrangeConstant(x0, fx0, x1, x2, x3))
            , c1(lagrangeConstant(x1, fx1, x0, x2, x3))
            , c2(lagrangeConstant(x2, fx2, x0, x1, x3))
            , c3(lagrangeConstant(x3, fx3, x0, x1, x2)){}

            uint8_t f(const float x){
                const float dx0=x-x0, dx1=x-x1, dx2=x-x2, dx3=x-x3;
                const float xc0=dx1*dx2*dx3, xc1=dx0*dx2*dx3, xc2=dx0*dx1*dx3, xc3=dx0*dx1*dx2;
                const float l0=xc0/c0, l1=xc1/c1, l2=xc2/c2, l3=xc3/c3;

                return static_cast<uint8_t>(l0*fx0 + l1*fx1 + l2*fx2 + l3*fx3);
            }
        };

        inline int cubic_interpolation(const float x,
            const int x0, const uint8_t fx0,
            const int x1, const uint8_t fx1,
            const int x2, const uint8_t fx2,
            const int x3, const uint8_t fx3
        ){

        }

        inline uint8_t quadratic(const Mat& src, const float x, const float y){
            if(isMatOutside(src, x, y))
                return BLACK;

            const int x0=max(static_cast<int>(x), 0);
            const int x1=max(static_cast<int>(x0-1), 0);
            const int x2=min(static_cast<int>(x0+1), src.cols-1);
            const int x3=min(static_cast<int>(x0+2), src.cols-1);

            const int index=static_cast<int>(src.cols*y);
            const uint8_t fx0=src.data[index + x0];
            const uint8_t fx1=src.data[index + x1];
            const uint8_t fx2=src.data[index + x0];
            const uint8_t fx3=src.data[index + x1];

            LagrangeCubic lc()



            const float len_x0=x-x0;
            const float len_x1=1-len_x0;
            const float len_y0=y-y0;
            const float len_y1=1-len_y0;

            const float weight_y0x0=len_y0*len_x0;
            const float weight_y0x1=len_y0*len_x1;
            const float weight_y1x0=len_y1*len_x0;
            const float weight_y1x1=len_y1*len_x1;

            return weight_y1x1*y0x0 + weight_y1x0*y0x1 +
                weight_y0x1*y1x0 + weight_y0x0*y1x1;
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

                    const float x_origin =  cos_d*x_dst + sin_d*y_dst + mid_x;
                    const float y_origin = -sin_d*x_dst + cos_d*y_dst + mid_y;

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

    {
        TimeGuard tg{};
        for(int i=0; i<100; ++i)
            Mat Lena_436x436_replicate=resize(source, 436, 436, replicate);
        // matshow(Lena_436x436_replicate);
    }
    {
        TimeGuard tg{};
        for(int i=0; i<100; ++i)
            Mat Lena_436x436_nearest=resize(source, 436, 436, nearest);
        // matshow(Lena_436x436_nearest);
    }
    {
        TimeGuard tg{};
        for(int i=0; i<100; ++i)
            Mat Lena_436x436=resize(source, 436, 436, bilinear);
        // matshow(Lena_436x436);
    }

    // Mat Lena_512x512=resize(source, 512, 512, bilinear);
    // matshow(Lena_512x512);
    // Mat Lena_512x512_wrong=resize(source, 512, 512, bilinear_wrong);
    // matshow(Lena_512x512_wrong);

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
