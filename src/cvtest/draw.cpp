#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void){
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
