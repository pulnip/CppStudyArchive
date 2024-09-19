#include <opencv2/opencv.hpp>
#include "cvtestfwd.hpp"

using namespace cv;

#define nameof(x) (#x)
#define myshow(x) (imshow(nameof(x), (x)))

#define CLIP(x) (max(min((x), 0xff), 0x00))

static Mat colorBox(const Size& size, uint8_t color){
    auto dst=Mat(size, CV_8UC3);

    for(int i=0; i<dst.rows*dst.cols; ++i){
        dst.data[3*i + 0]=color;
        dst.data[3*i + 1]=color;
        dst.data[3*i + 2]=color;
    }

    return dst;

}

static Mat rotateX(const Mat& src){
    auto dst=Mat(src.size(), CV_8UC3);

    for(int i=0; i<src.rows; ++i){
        int idx=3*src.cols*i;

        for(int j=0; j<src.cols; ++j){
            int offset=3*j;
            int rev=3*(src.cols-j-1);
            dst.data[idx + offset + 0]=src.data[idx + rev + 0];
            dst.data[idx + offset + 1]=src.data[idx + rev + 1];
            dst.data[idx + offset + 2]=src.data[idx + rev + 2];
        }
    }

    return dst;
}

static Mat rotateY(const Mat& src){
    auto dst=Mat(src.size(), CV_8UC3);

    for(int i=0; i<src.rows; ++i){
        int idx=3*src.cols*i;
        int rev=3*src.cols*(src.rows-i-1);

        for(int j=0; j<src.cols; ++j){
            int offset=3*j;
            dst.data[idx + offset + 0]=src.data[rev + offset + 0];
            dst.data[idx + offset + 1]=src.data[rev + offset + 1];
            dst.data[idx + offset + 2]=src.data[rev + offset + 2];
        }
    }

    return dst;
}

static Mat reverse(const Mat& src){
    auto dst=Mat(src.size(), CV_8UC3);

    for(int i=0; i<src.rows*src.cols; ++i){
        dst.data[3*i + 0]=0xff-src.data[3*i + 0];
        dst.data[3*i + 1]=0xff-src.data[3*i + 1];
        dst.data[3*i + 2]=0xff-src.data[3*i + 2];
    }

    return dst;
}

static Mat sum(const Mat& src, const Mat& addend){
    auto dst=Mat(src.size(), CV_8UC3);

    for(int i=0; i<src.rows*src.cols; ++i){
        dst.data[3*i + 0]=CLIP(src.data[3*i + 0] + addend.data[3*i + 0]);
        dst.data[3*i + 1]=CLIP(src.data[3*i + 1] + addend.data[3*i + 1]);
        dst.data[3*i + 2]=CLIP(src.data[3*i + 2] + addend.data[3*i + 2]);
    }

    return dst;
}

static Mat average(const Mat& src, const Mat& addend){
    auto dst=Mat(src.size(), CV_8UC3);

    for(int i=0; i<src.rows*src.cols; ++i){
        dst.data[3*i + 0]=(src.data[3*i + 0] + addend.data[3*i + 0]) >> 1;
        dst.data[3*i + 1]=(src.data[3*i + 1] + addend.data[3*i + 1]) >> 1;
        dst.data[3*i + 2]=(src.data[3*i + 2] + addend.data[3*i + 2]) >> 1;
    }

    return dst;
}

static Mat subtract(const Mat& src, const Mat& sub){
    auto dst=Mat(src.size(), CV_8UC3);

    for(int i=0; i<src.rows*src.cols; ++i){
        dst.data[3*i + 0]=CLIP(src.data[3*i + 0] - sub.data[3*i + 0]);
        dst.data[3*i + 1]=CLIP(src.data[3*i + 1] - sub.data[3*i + 1]);
        dst.data[3*i + 2]=CLIP(src.data[3*i + 2] - sub.data[3*i + 2]);
    }

    return dst;
}

int cvtest::transform(){
    Mat src=imread("Lena.png");
    myshow(src);

    auto rotX=rotateX(src);
    // myshow(rotX);
    // auto rotY=rotateY(src);
    // myshow(rotY);
    // auto rotXY=rotateY(rotX);
    // myshow(rotXY);

    // auto rev=reverse(src);
    // myshow(rev);

    // auto avg=average(src, rev);
    // myshow(avg);

    // auto brt=sum(src, colorBox(src.size(), 70));
    // myshow(brt);

    // auto drk=subtract(src, colorBox(src.size(), 70));
    // myshow(drk);

    auto avg=average(src, rotX);
    myshow(avg);

    waitKey(0);
    return 0;
}

#undef nameof
#undef myshow
#undef CLIP
