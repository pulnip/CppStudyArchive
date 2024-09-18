#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "cvtestfwd.hpp"

using namespace std;
using namespace cv;

static bool clicked=false;
static int startX, startY, currX, currY;

static vector<Mat> video;
static int videoPtr=0;
static Mat tmp;


static void onMouse(int evt, int x, int y, int flags, void* param){
    switch(evt){
    case EVENT_LBUTTONDOWN:
        clicked=true;
        startX=currX=x; startY=currY=y;
        break;
    case EVENT_LBUTTONUP:
        clicked=false;
        video[videoPtr]=tmp;
        break;
    case EVENT_MOUSEMOVE:
        currX=x; currY=y;
        break;
    }
}

static void loadVideo(const string& fileName){
    VideoCapture capture(fileName);
    if(!capture.isOpened()){
        puts("cannot open Video file.");
        return;
    }

    while(true){
        Mat frame;
        capture>>frame;

        if(frame.empty())
            break;

        resize(frame, frame, Size(640, 360));
        video.push_back(frame);
    }
}

static void setNextFrame(){
    videoPtr=min<int>(videoPtr+1, video.size()-1);
    imshow("Video Player", video[videoPtr]);
}

static void setPrevFrame(){
    videoPtr=max<int>(videoPtr-1, 0);
    imshow("Video Player", video[videoPtr]);
}

int cvtest::videoplayer(){
    loadVideo("testVideo.mp4");
    if(video.empty())
        return 0;

    imshow("Video Player", video[videoPtr]);
    setMouseCallback("Video Player", onMouse, &video[videoPtr]);

    bool active=true;
    bool keyup=true;
    bool play=false;

    while(active){
        switch(waitKey(33)){
        case 'q':
            active=false;
            break;
        case ' ':
            if(keyup){
                keyup=false;
                play=!play;
            }
            break;
        case 'p':
            if(!play)
                setNextFrame();
            break;
        case 'n':
            if(!play)
                setPrevFrame();
            break;
        case -1:
            keyup=true;
            break;
        }

        if(play){
            setNextFrame();
        }
        else if(clicked){
            tmp=video[videoPtr].clone();
            line(tmp, Point(startX, startY), Point(currX, currY),
                Scalar(255, 255, 255), 5);
            imshow("Video Player", tmp);
        }
    }

    return 0;
}
