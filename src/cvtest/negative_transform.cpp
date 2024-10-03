#include <opencv2/opencv.hpp>

using namespace cv;

#define nameof(x) (#x)
#define matshow(x) (imshow(nameof(x), x))

uint8_t neg(uint8_t r){ return 255-r; }

Mat transform(const Mat& src, uint8_t (*f)(uint8_t)){
    Mat dst=src.clone();

    for(int i=0; i<dst.rows*dst.cols; ++i)
        dst.data[i]=f(dst.data[i]);

    return dst;
}

int main(void){
	Mat source=imread("Lena_256x256.png", IMREAD_GRAYSCALE);
    matshow(source);

    Mat transformed=transform(source, neg);
    matshow(transformed);

	waitKey(0);
	return 0;
}

#undef nameof
#undef matshow
