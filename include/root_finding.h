#pragma once 

#include "base.h"

#define ROOT_FINDER_F0(x) extern double x(continuous_function f, \
    double p0, double p1, double TOL, int N0)
#define ROOT_FINDER_F1(x) extern double x( \
    continuous_function f0, derivative f1, \
    double p0, double p1, double TOL, int N0)

#ifdef __cplusplus
extern "C"{
#endif

ROOT_FINDER_F0(bisection);
ROOT_FINDER_F0(secant);
ROOT_FINDER_F1(newton);

#ifdef __cplusplus
}
#endif

#undef ROOT_FINDER_F0
#undef ROOT_FINDER_F1
