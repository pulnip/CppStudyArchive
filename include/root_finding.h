#pragma once 

typedef double(*continuous_function)(double);
typedef double(*derivative)(double);

#define ROOT_FINDER_F0(x) extern double x(continuous_function f, \
    double p0, double p1, double TOL, int N0)
#define ROOT_FINDER_F1(x) extern double x( \
    continuous_function f0, derivative f1, \
    double p0, double p1, double TOL, int N0)

ROOT_FINDER_F0(bisection);
ROOT_FINDER_F0(secant);
ROOT_FINDER_F1(newton);

#undef ROOT_FINDER_F0
#undef ROOT_FINDER_F1
