#include <print>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void){
    Mat mat=imread("Lena.png", IMREAD_COLOR);
    namedWindow("cvtest", WINDOW_AUTOSIZE);
    imshow("cvtest", mat);

    waitKey(0);
    return 0;
}
