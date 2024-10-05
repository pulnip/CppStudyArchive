#include <iostream>
#include <Windows.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include "fwd.hpp"

using namespace std;
using namespace cv;

class hwnd2Mat{
    HWND hwnd;
    HDC hwindowDC, hwindowCompatibleDC;
    int height, width, srcheight, srcwidth;
    HBITMAP hbwindow;
    BITMAPINFOHEADER  bi;

  public:
    Mat image;

  public:
    hwnd2Mat(HWND hwindow, float scale=1);
    virtual ~hwnd2Mat();
    virtual void read();
};

BITMAPINFOHEADER createBitmapHeader(int width, int height){
    // http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
    return BITMAPINFOHEADER{
        .biSize=sizeof(BITMAPINFOHEADER),
        .biWidth=width,
        // draw upside down or not
        .biHeight=-height,
        .biPlanes=1,
        .biBitCount=32,
        .biCompression=BI_RGB,
        .biSizeImage=0,
        .biXPelsPerMeter=0,
        .biYPelsPerMeter=0,
        .biClrUsed=0,
        .biClrImportant=0
    };
}

hwnd2Mat::hwnd2Mat(HWND hwindow, float scale){
    // get handles to a device context
    hwnd=hwindow;
    hwindowDC=GetDC(hwnd);
    hwindowCompatibleDC=CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

    // get the height and width of the screen
    RECT windowsize;
    GetClientRect(hwnd, &windowsize);

    srcheight=windowsize.bottom;
    srcwidth=windowsize.right;
    height=(int)(windowsize.bottom * scale);
    width=(int)(windowsize.right * scale);

    // create mat object
    image.create(height, width, CV_8UC4);

    // create a bitmap
    hbwindow=CreateCompatibleBitmap(hwindowDC, width, height);
    bi=createBitmapHeader(width, height);

    // use the previously created device context with the bitmap
    SelectObject(hwindowCompatibleDC, hbwindow);
    read();
};

void hwnd2Mat::read(){
    // copy from the window device context to the bitmap device context
    StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY);
    // copy from hwindowCompatibleDC to hbwindow
    GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, image.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
};

hwnd2Mat::~hwnd2Mat(){
    // avoid memory leak
    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);
};

int cvtest::screenshot(void){
    Mat ui(40, 400, CV_8UC3, Scalar(0, 130, 0));
    putText(ui, "Press Esc to stop capturing", Point(30,30),
        FONT_HERSHEY_COMPLEX, 0.7, Scalar(0, 0, 255), 1);
    Mat bgrImg;
    hwnd2Mat capDesktop(GetDesktopWindow());

    VideoWriter writer;
    int codec=VideoWriter::fourcc('X', 'V', 'I', 'D');
    double fps=10.0;
    string filename="./desktop_capture.avi";
    writer.open(filename, codec, fps, capDesktop.image.size(), true);
    // check if we succeeded
    if(!writer.isOpened()){
        cerr<<"Could not open the output video file for write\n";
        return -1;
    }

    while(true){
        capDesktop.read();
        cvtColor(capDesktop.image, bgrImg, COLOR_BGRA2BGR);
        writer << bgrImg;
        imshow("desktop capture", ui);
        int key=waitKey(5);

        if(key == 27)
            break;
    }

    return 0;
}