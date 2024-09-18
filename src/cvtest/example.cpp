// PSNR.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#include <print>
#include <cmath>

// #include <opencv2/cvv.hpp>
// #include <opencv2/cv.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main2(){
	Mat img_in=imread("Lena_256x256.png");
	cvtColor(img_in, img_in, COLOR_RGB2GRAY);
	imshow("source img", img_in);

    println("src: {}x{}", img_in.rows, img_in.cols);

    constexpr int x_size=512, y_size=512;
    const auto x_scale=static_cast<float>(img_in.cols)/x_size;
    const auto y_scale=static_cast<float>(img_in.rows)/y_size;
    Mat img_out(y_size, x_size, COLOR_RGB2GRAY);
	
    println("dst: {}x{}", img_out.rows, img_out.cols);
    println("scale: {}, {}", x_scale, y_scale);

    for(int i=0; i<y_size; ++i){
        const auto y0=static_cast<int>(y_scale*i);
        for(int j=0; j<x_size; ++j){
            const auto x0=static_cast<int>(x_scale*j);

            img_out.data[x_size*i + j]=img_in.data[img_in.cols*y0 + x0];
        }
    }
	imshow("output image", img_out);

	waitKey(0);

	return 0;
}
