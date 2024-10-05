#pragma once

#include <cmath>
#include <opencv2/opencv.hpp>

namespace cvtest{
    using pixel=uint8_t;
    using entrypoint=int(void);

    constexpr pixel BLACK=0x00;
    constexpr pixel WHITE=0xff;

    entrypoint drawLine;
    entrypoint drawAtVideo;
    entrypoint screenshot;
    entrypoint drawHistogram;
    entrypoint simple_videoplayer;

    template<typename T>
    inline constexpr T clip(T x, T m, T M){ return std::min(std::max(x, m), M); }

    namespace factory{
        cv::Mat simpleImage_grayscale(const cv::Size& size, pixel color);
        cv::Mat simpleImage(const cv::Size& size, pixel r, pixel g, pixel b);
    }

    namespace interpolation{
        using boundary_check_t=bool(const cv::Mat&, float, float);
        using interpolate_grayscale_t=pixel(const cv::Mat&, float, float);

        boundary_check_t isMatOutside;

        interpolate_grayscale_t replicate_grayscale;
        interpolate_grayscale_t nearest_grayscale;
        interpolate_grayscale_t bilinear_grayscale;
        interpolate_grayscale_t bicubic_grayscale;
    }

    namespace geometry_transformation{
        cv::Mat resize_grayscale(const cv::Mat& src,
            const int x_size, const int y_size,
            interpolation::interpolate_grayscale_t itpl
        );
        cv::Mat rotate_grayscale(const cv::Mat& src,
            float radian,
            interpolation::interpolate_grayscale_t itpl
        );

        cv::Mat flipX_grayscale(const cv::Mat&);
        cv::Mat flipY_grayscale(const cv::Mat&);
        cv::Mat flipX(const cv::Mat&);
        cv::Mat flipY(const cv::Mat&);
    }

    namespace image_analyzer{
        cv::Mat getHistogram_grayscale(const cv::Mat&);

        class CDF{
            int freqs[256], cd[256];
            int min_cd, max_cd;

          public:
            CDF(const cv::Mat& src);
            CDF(int freq0, int x, int freqx, int freq255);

            // return normalized i-th cdf
            // range from 0.0 to 1.0
            float cd_normal(pixel p) const;
            // re-mapping i-th pixel using normalized value
            pixel inv(float normal) const;
        };
    }

    namespace image_transformation{
        using pixelwise_transform_grayscale_t=pixel(pixel);
        cv::Mat transform_grayscale(const cv::Mat& src,
            pixelwise_transform_grayscale_t f
        );
        cv::Mat transform(const cv::Mat& src, pixelwise_transform_grayscale_t f);

        pixelwise_transform_grayscale_t neg;
        pixelwise_transform_grayscale_t half_black;
        pixelwise_transform_grayscale_t half_white;

        template<uint8_t threshold_val, uint8_t m=BLACK>
        constexpr pixel threshold_lt(pixel p){ return p < threshold_val ? m : p; }

        using bipixel_transform_grayscale_t=pixel(pixel, pixel);
        cv::Mat transform_grayscale(const cv::Mat& lhs, const cv::Mat& rhs,
            bipixel_transform_grayscale_t f
        );
        cv::Mat transform(const cv::Mat& lhs, const cv::Mat& rhs,
            bipixel_transform_grayscale_t f
        );
        bipixel_transform_grayscale_t sum;
        bipixel_transform_grayscale_t average;
        bipixel_transform_grayscale_t subtract;

        cv::Mat gamma_grayscale(const cv::Mat& src, float gamma);
        cv::Mat equalizeHistogram_grayscale(const cv::Mat& src);
        cv::Mat matchHistogram_grayscale(const cv::Mat& src,
            const image_analyzer::CDF& hist
        );
    }
}
