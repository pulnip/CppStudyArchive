#include <cmath>
#include <opencv2/opencv.hpp>

using namespace cv;

#define nameof(x) (#x)
#define matshow(x) (imshow(nameof(x), x))

Mat gamma_transform(const Mat& src, const float gamma){
    Mat dst=src.clone();

    for(int i=0; i<dst.rows*dst.cols; ++i)
        dst.data[i]=255 * std::pow(dst.data[i]/255.0f, gamma);

    return dst;
}

int main(void){
	Mat source=imread("Lena_256x256.png", IMREAD_GRAYSCALE);
    matshow(source);

    Mat gamma0_5=gamma_transform(source, 0.5f);
    matshow(gamma0_5);
    Mat gamma1_5=gamma_transform(source, 1.5f);
    matshow(gamma1_5);

	waitKey(0);
	return 0;
}

#undef nameof
#undef matshow
