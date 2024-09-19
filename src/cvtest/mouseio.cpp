#include <iostream>
#include <opencv2/highgui.hpp>

using namespace cv;

static void onMouse(int evt, int x, int y, int flags, void* param){
    switch(evt){
        case EVENT_LBUTTONDOWN:
            puts("L button down");
            break;
        case EVENT_LBUTTONUP:
            puts("L button up");
            break;
        case EVENT_MOUSEMOVE:
            puts("+");
            break;
    }
}

int main(void){
    Mat screen=Mat::zeros(512, 512, CV_8UC3);
    imshow("screen", screen);

    setMouseCallback("screen", onMouse, &screen);

    waitKey(0);
    return 0;
}
