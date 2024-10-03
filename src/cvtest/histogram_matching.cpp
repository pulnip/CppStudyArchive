#include <array>
#include <opencv2/opencv.hpp>

#include <print>

using namespace std;
using namespace cv;

#define nameof(x) (#x)
#define matshow(x) (imshow(nameof(x), x))

class CDF{
  private:
    array<int, 256> freqs={0, }, cdfs;
    int min_cdf, max_cdf;

  public:
    CDF(const Mat& src){
        for(int i=0; i<src.rows*src.cols; ++i)
            ++freqs[src.data[i]];

        cdfs[0]=min_cdf=max_cdf=freqs[0];

        for(int i=1; i<256; ++i){
            cdfs[i]=cdfs[i-1]+freqs[i];

            if(max_cdf < cdfs[i])
                max_cdf=cdfs[i];
            else if(cdfs[i] < min_cdf)
                min_cdf=cdfs[i];
        }
    }
    CDF(int freq0, int x, int freqx, int freq255){
        for(int i=0; i<256; ++i){
            freqs[i]= i<x ?
                freq0 + (static_cast<float>(i-0)/(  x-0)) * (freqx  -freq0):
                freqx + (static_cast<float>(i-x)/(256-x)) * (freq255-freqx);
        }

        cdfs[0]=min_cdf=max_cdf=freqs[0];

        for(int i=1; i<256; ++i){
            cdfs[i]=cdfs[i-1]+freqs[i];

            if(max_cdf < cdfs[i])
                max_cdf=cdfs[i];
            else if(cdfs[i] < min_cdf)
                min_cdf=cdfs[i];
        }
    }

    float cdf(uint8_t i) const{
        return static_cast<float>(cdfs[i]-min_cdf) / (max_cdf-min_cdf);
    }

    uint8_t inv(float x) const{
        for(int i=0; i<256; ++i){
            float p=static_cast<float>(cdfs[i]-min_cdf) / (max_cdf-min_cdf);
            if(x<=p)
                return i;
        }

        return 255;
    }
};

uint8_t match(uint8_t l, const CDF& origin, const CDF& spec){
    return spec.inv(origin.cdf(l));
}

Mat matchHistogram(const Mat& src, const CDF& hist){
    Mat dst=src.clone();
    CDF src_cdf(dst);

    for(int i=0; i<dst.rows*dst.cols; ++i){
        dst.data[i]=match(dst.data[i], src_cdf, hist);
    }

    return dst;
}


int main(void){
	Mat source=imread("Lena_256x256.png", IMREAD_GRAYSCALE);
    matshow(source);

    CDF target(100, 90, 150, 80);

    Mat matched=matchHistogram(source, target);
    matshow(matched);

	waitKey(0);
	return 0;
}

#undef nameof
#undef matshow
