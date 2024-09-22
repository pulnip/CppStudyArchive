#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "natest/root_finding.h"

void bisection(double(*f)(double), double a, double b,
    const double TOL, const int n0
){
    double fa=f(a);
    int inc=fa<0;

    assert(a < b);
    assert(TOL > 0);
    assert(n0 > 0);
    assert(fa*fb < 0);

    puts("_n|______________an|______________bn|______________pn|___________f(pn)");
    for(int i=1; i<n0; ++i){
        double p=(a+b)/2;
        double fp=f(p);
        if((fabs(b-a) < TOL) || (fp == 0))
            break;

        printf("% 2d|% 16.10lf|% 16.10lf|% 16.10lf|% 16.10lf\n", i, a, b, p, fp);

        if(fp < 0){
            if(inc) a=p;
            else b=p;
        }
        else{
            if(inc) b=p;
            else a=p;
        }
    }
}

void secant(double(*f)(double), double p0, double p1,
    const double TOL, const int n0
){
    assert(TOL > 0);
    assert(n0 > 0);

    puts("_n|______________pn|___________f(pn)");
    for(int i=2; i<n0; ++i){
        if(fabs(p1-p0) < TOL)
            break;

        double fp0=f(p0), fp1=f(p1);
        double p=(p0*fp1 - p1*fp0)/(fp1-fp0);
        double fp=f(p);
        printf("% 2d|% 16.10lf|% 16.10lf\n", i, p, fp);

        if(fp == 0)
            break;

        p0=p1;
        p1=p;
    }
}

void newton(double(*fp0)(double), double(*fp1)(double),
    double x0, double x1,
    const double TOL, const int n0
){
    double p0=(x0 + x1)/2;

    puts("_n|______________pn|____abs(pn-pn-1)");
    puts(" 0|    0.5000000000|");
    for(int i=1; i<n0; ++i){
        double p=p0 - fp0(p0)/fp1(p0);
        double e=fabs(p-p0);

        printf("% 2d|% 16.10lf|% 16.10lf\n", i, p, e);
        if(e < TOL)
            break;

        p0=p;
    }
}
