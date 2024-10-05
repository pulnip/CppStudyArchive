#include <gtest/gtest.h>
#include "fwd.hpp"

using namespace cvtest;
using namespace cvtest::image_transformation;

TEST(cvtestTest, TemplateTest){
    constexpr uint8_t GRAY=128;
    constexpr uint8_t DARKER=127;

    constexpr auto _clip=[](int i){ return clip<int>(i, BLACK, WHITE); };

    static_assert(_clip(-43)==BLACK);
    static_assert(_clip( 34)==   34);
    static_assert(_clip(256)==WHITE);

    constexpr auto threshold=threshold_lt<GRAY>;

    static_assert(threshold(GRAY)==GRAY);
    static_assert(threshold(DARKER)==BLACK);
}
