#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main3(void){
    VideoCapture capture("testVideo.mp4");
    Mat frame;

    if(!capture.isOpened()){
        puts("cannot open Video file.");
        return 0;
    }

    namedWindow("video");

    while(true){
        capture>>frame;

        if(frame.empty())
            break;

        imshow("video", frame);
        if(waitKey(1)>0)
            break;
    }

    return 0;
}
