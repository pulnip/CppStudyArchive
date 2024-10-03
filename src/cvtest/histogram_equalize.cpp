#include <array>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define nameof(x) (#x)
#define matshow(x) (imshow(nameof(x), x))

uint8_t r2(uint8_t r){ return r>>1; }
uint8_t r2_128(uint8_t r){ return (r>>1) + 128; }

// f is pixel-wise transform function
Mat transform(const Mat& src, uint8_t (*f)(uint8_t)){
    Mat dst=src.clone();

    // apply f per pixel
    for(int i=0; i<dst.rows*dst.cols; ++i)
        dst.data[i]=f(dst.data[i]);

    return dst;
}

class CDF{
  private:
    array<int, 256> freqs={0, }, cdfs;
    int min_cdf, max_cdf;

  public:
    CDF(const Mat& src){
        // calculate frequency of Mat
        for(int i=0; i<src.rows*src.cols; ++i)
            ++freqs[src.data[i]];

        // cummulate from 0 to 0 is the smallest
        cdfs[0]=min_cdf=freqs[0];

        // calculate cummulative distribution
        for(int i=1; i<256; ++i){
            cdfs[i]=cdfs[i-1]+freqs[i];
        }

        // cummulate from 0 to 255 is the largest
        max_cdf=cdfs[255];
    }

    float cdf(uint8_t i) const{
        // return normalized i-th cdf
        // range from 0.0 to 1.0
        return static_cast<float>(cdfs[i]-min_cdf) / (max_cdf-min_cdf);
    }
};

Mat equalizeHistogram(const Mat& src){
    Mat dst=src.clone();
    CDF src_cdf(dst);

    for(int i=0; i<dst.rows*dst.cols; ++i){
        // re-mapping i-th pixel using normalized value
        // mul 255 for [0.0, 1.0] to [0, 255] (range of uint8_t)
        dst.data[i]=255*src_cdf.cdf(dst.data[i]);
    }

    return dst;
}

int main(void){
    // original image
	Mat source=imread("Lena_256x256.png", IMREAD_GRAYSCALE);
    matshow(source);
    // transform s=r/2
    Mat transformed_r2=transform(source, r2);
    matshow(transformed_r2);
    // transform s=r/2+128
    Mat transformed_r2_128=transform(source, r2_128);
    matshow(transformed_r2_128);

    // apply histogram equalization
    Mat src_eq=equalizeHistogram(source);
    matshow(src_eq);
    Mat t_r2_eq=equalizeHistogram(transformed_r2);
    matshow(t_r2_eq);
    Mat t_r2_128_eq=equalizeHistogram(transformed_r2_128);
    matshow(t_r2_128_eq);

	waitKey(0);
	return 0;
}

#undef nameof
#undef matshow
