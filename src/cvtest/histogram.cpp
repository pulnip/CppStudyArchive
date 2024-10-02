#include <algorithm>
#include <print>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define nameof(x) (#x)
#define matshow(x) (imshow(nameof(x), x))

inline Mat getHistogram(const Mat& src){
    Mat dst(256, 256, CV_8UC1);

    int freq[256]={0, };
    for(int i=0; i<src.rows*src.cols; ++i){
        ++freq[src.data[i]];
    }

    int max_freq=freq[0], min_freq=freq[0];
    for(int i=1; i<256; ++i){
        if(max_freq < freq[i])
            max_freq=freq[i];
        else if(freq[i] < min_freq)
            min_freq=freq[i];
    }

    for(int x=0; x<256; ++x){
        int y=255 * (static_cast<float>(freq[x]-min_freq)/(max_freq-min_freq));
        println("{}", y);

        for(int i=0; i<y; ++i){
            dst.data[256*y+x] = 0xff;
        }
        for(int i=y; i<256; ++i){
            dst.data[256*y+x] = 0x00;
        }
    }

    return dst;
}

int main(void){
	Mat source=imread("Lena_256x256.png", IMREAD_GRAYSCALE);
    matshow(source);

    Mat histogram=getHistogram(source);
    matshow(histogram);

	waitKey(0);
	return 0;
}

#undef _USE_MATH_DEFINES
#undef nameof
#undef matshow
