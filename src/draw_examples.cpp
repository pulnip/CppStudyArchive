#include <print>
#include <vector>
#include <opencv2/opencv.hpp>
#include "fwd.hpp"

using namespace std;
using namespace cv;
using namespace cvtest;

static bool clicked=false;
static int startX, startY, currX, currY;

static Mat src;
static Mat tmp;

static void onMouse(int evt, int x, int y,
    [[maybe_unused]] int flags, [[maybe_unused]] void* param
){
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

int cvtest::drawLine(void){
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

int cvtest::drawAtVideo(void){
    VideoCapture capture("testVideo.mp4");
    if(!capture.isOpened()){
        puts("cannot open Video file.");
        return 0;
    }

    VideoWriter writer;
    vector<Mat> video;

    writer.open("NewVideo.mp4", VideoWriter::fourcc('m', 'p', '4', 'v'),
        30, Size(640, 360), true
    );

    for(size_t i=0; i<1000; ++i){
        Mat frame;
        capture>>frame;
        if(frame.empty())
            break;

        Mat frame_s;
        resize(frame, frame_s, Size(640, 360));
        circle(frame_s, Point(320, 160), i+10, Scalar(0, 0, 255), 5);

        video.push_back(frame_s);
    }

    for(size_t i=0; i<video.size(); ++i){
        writer.write(video[video.size() - (i+1)]);
    }

    return 0;
}
