#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main1(void){
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

int main2(void){
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

    while(true){
        Mat frame;
        capture>>frame;
        if(frame.empty())
            break;

        Mat frame_s;
        resize(frame, frame_s, Size(640, 360));

        video.push_back(frame_s);
    }

    for(size_t i=0; i<video.size(); ++i){
        writer.write(video[video.size() - (i+1)]);
    }

    return 0;
}
