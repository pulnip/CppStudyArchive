#include <print>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]){
    Mat mat=imread("assets/lenna.png", IMREAD_COLOR);
    namedWindow("cvtest", WINDOW_AUTOSIZE);
    imshow("cvtest", mat);

    waitKey(0);

    return 0;
}
