#include <iostream>
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "cvtestfwd.hpp"

using namespace std;
using namespace cv;

bool clicked=false;
int startX, startY, currX, currY;

static void onMouse(int evt, int x, int y, int flags, void* param){
    switch(evt){
        case EVENT_LBUTTONDOWN:
            clicked=true;
            startX=currX=x; startY=currY=y;
            break;
        case EVENT_LBUTTONUP:
            clicked=false;
            break;
        case EVENT_MOUSEMOVE:
            currX=x; currY=y;
            break;
    }
}

int cvtest::practice(){
    Mat src=imread("Lena.png");
    imshow("screen", src);
    setMouseCallback("screen", onMouse, &src);

    // while(true){
        if(clicked){
            line(src, Point(startX, startY), Point(currX, currX),
                Scalar(255, 255, 255), 7);
            Mat tmp=src;
            imshow("screen", tmp);
        }
    // }

    waitKey(0);

    return 0;
}