#pragma once

#include <chrono>
#include <opencv2/opencv.hpp>

#define nameof(x) (#x)
#define matshow(x) (cv::imshow(nameof(x), x))

class TimeGuard{
    using Clock=std::chrono::high_resolution_clock;
    using TimePoint=std::chrono::time_point<Clock>;

    TimePoint start=Clock::now();

  public:
    TimeGuard()=default;
    ~TimeGuard();
};