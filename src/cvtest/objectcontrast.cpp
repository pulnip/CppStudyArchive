#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define nameof(x) (#x)
#define matshow(x) (imshow(nameof(x), x))

constexpr uint8_t WHITE=0xff;
constexpr uint8_t BLACK=0x00;

struct rgb{ uint8_t r, g, b; };

inline rgb diff(const Mat& src, int x, int y, uint8_t threshold){
    const int x_u=3*src.cols*y + 3*x;
    const int xnn=3*src.cols*y + 3*src.cols;
    const int x_1=x_u+3<xnn ? x_u+3 : 0;

    const bool r_ex = src.data[x_1+0]-src.data[x_u+0] > threshold;
    const bool g_ex = src.data[x_1+1]-src.data[x_u+1] > threshold;
    const bool b_ex = src.data[x_1+2]-src.data[x_u+2] > threshold;

    return r_ex||g_ex||b_ex ?
        rgb{src.data[x_u+0], src.data[x_u+1], src.data[x_u+2]} :
        rgb{BLACK, BLACK, BLACK};
}

inline Mat objectconstrast(const Mat& src, uint8_t threshold){
    Mat dst(src.rows, src.cols, CV_8UC3);

    for(int i=0; i<src.rows; ++i){
        const int index=3*src.cols*i;

        for(int j=0; j<src.cols; ++j){
            const int offset=3*j;
            const int idx=index+offset;

            rgb res=diff(src, j, i, threshold);
            dst.data[idx + 0]=res.r;
            dst.data[idx + 1]=res.g;
            dst.data[idx + 2]=res.b;
        }
    }

    return dst;
}

int main(void){
	Mat source=imread("Lena_256x256.png");
    matshow(source);

    // Mat diff4=objectconstrast(source, 4);
    // matshow(diff4);
    // Mat diff8=objectconstrast(source, 8);
    // matshow(diff8);
    Mat diff12=objectconstrast(source, 12);
    matshow(diff12);
    Mat diff16=objectconstrast(source, 16);
    matshow(diff16);

	waitKey(0);
	return 0;
}

#undef _USE_MATH_DEFINES
#undef nameof
#undef matshow
