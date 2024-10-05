#include "fwd.hpp"

using namespace cv;
using namespace cvtest;
using namespace cvtest::image_analyzer;

CDF::CDF(const Mat& src){
    for(int i=0; i<src.rows*src.cols; ++i)
        ++freqs[src.data[i]];

    cd[0]=min_cd=freqs[0];

    for(int i=1; i<256; ++i)
        cd[i]=cd[i-1]+freqs[i];

    max_cd=cd[255];
}

CDF::CDF(int freq0, int x, int freqx, int freq255){
    for(int i=0; i<256; ++i){
        freqs[i]= i<x ?
            freq0 + (static_cast<float>(i-0)/(  x-0)) * (freqx  -freq0):
            freqx + (static_cast<float>(i-x)/(256-x)) * (freq255-freqx);
    }

    cd[0]=min_cd=freqs[0];

    for(int i=1; i<256; ++i)
        cd[i]=cd[i-1]+freqs[i];

    max_cd=cd[255];
}

float CDF::cd_normal(pixel i) const{
    return static_cast<float>(cd[i]-min_cd) / (max_cd-min_cd);
}

pixel CDF::inv(float normal) const{
    for(int i=0; i<256; ++i){
        float p=static_cast<float>(cd[i]-min_cd) / (max_cd-min_cd);
        if(normal<=p)
            return i;
    }

    return 255;
}
