#pragma once

#include "base.h"

#ifdef __cplusplus
extern "C"{
#endif

extern double simpson(continuous_function f, double a, double b);
extern double adaptive_quadrature(continuous_function f, double a, double b, double TOL);

#ifdef __cplusplus
}
#endif