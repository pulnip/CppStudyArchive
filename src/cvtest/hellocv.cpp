#include <print>
#include <opencv2/opencv.hpp>
#include "cvtestfwd.hpp"

using namespace std;
using namespace cv;

int cvtest::hellocv(){
    Mat mat=imread("Lena.png", IMREAD_COLOR);
    namedWindow("cvtest", WINDOW_AUTOSIZE);
    imshow("cvtest", mat);

    waitKey(0);

    return 0;
}
