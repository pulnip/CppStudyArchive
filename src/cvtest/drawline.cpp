#include <iostream>
#include <opencv2/opencv.hpp>
#include "cvtestfwd.hpp"

using namespace std;
using namespace cv;

static bool clicked=false;
static int startX, startY, currX, currY;

static Mat src;
static Mat tmp;

static void onMouse(int evt, int x, int y, int flags, void* param){
    switch(evt){
        case EVENT_LBUTTONDOWN:
            clicked=true;
            startX=currX=x; startY=currY=y;
            break;
        case EVENT_LBUTTONUP:
            clicked=false;
            src=tmp;
            break;
        case EVENT_MOUSEMOVE:
            currX=x; currY=y;
            break;
    }
}

int cvtest::drawline(){
    src=imread("Lena.png");
    imshow("screen", src);
    setMouseCallback("screen", onMouse, &src);

    while(waitKey(1)==-1){
        if(clicked){
            tmp=src.clone();
            line(tmp, Point(startX, startY), Point(currX, currY),
                Scalar(255, 255, 255), 5);
            imshow("screen", tmp);
        }
    }

    return 0;
}
