#pragma once 

extern void bisection(double(*f)(double), double a, double b, const double TOL, const int n0);
extern void secant(double(*f)(double), double p0, double p1, const double TOL, const int n0);
extern void newton(double(*fp0)(double), double(*fp1)(double), double x0, double x1, const double TOL, const int n0);
