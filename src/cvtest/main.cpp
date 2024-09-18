#include <print>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct RGBA{ uint8_t r, g, b, a; };
union U_t{ RGBA rgba; uint32_t i; };

int main1([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]){
    Mat mat=imread("assets/lenna.png", IMREAD_COLOR);
    namedWindow("cvtest", WINDOW_AUTOSIZE);

    println("row: {}, col: {}", mat.rows, mat.cols);

    using R_t=uint32_t;
    const auto& orig=mat.at<R_t>(0, 0);
    auto m=orig, M=orig;

    for(int i=0; i<mat.rows; ++i){
        for(int j=0; j<mat.cols; ++j){
            const auto& x=mat.at<R_t>(i, j);

            m=min(x, m);
            M=max(x, M);
        }
    }

    println("min: {:x}, Max: {:x}", m, M);

    imshow("cvtest", mat);

    waitKey(0);

    return 0;
}
