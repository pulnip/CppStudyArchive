#pragma once

#include "base.h"

#ifdef __cplusplus
extern "C"{
#endif

extern double gaussian(continuous_function f, double a, double b, int n);
extern double simpson(continuous_function f, double a, double b);
extern double adaptive(continuous_function f, double a, double b, double TOL);

#ifdef __cplusplus
}
#endif

#undef INTEGRAL
#undef ADAPTIVE