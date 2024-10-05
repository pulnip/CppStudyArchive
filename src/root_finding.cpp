#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "root_finding.h"

double bisection(continuous_function f,
    double a, double b,
    const double TOL, const int N0
){
    double fa=f(a), fb=f(b);
    int inc=fa<0;

    assert(a < b);
    assert(TOL > 0);
    assert(N0 > 0);
    assert(fa*fb < 0);

    double p;

#ifdef SHOW_INTERNAL_PROCESS
    puts("_n|______________an|______________bn|______________pn|___________f(pn)");
#endif
    for(int i=1; i<N0; ++i){
        p=(a+b)/2;
        double fp=f(p);

        if((fabs(b-a) < TOL) || (fp == 0))
            break;

#ifdef SHOW_INTERNAL_PROCESS
        printf("%2d|%16.10lf|%16.10lf|%16.10lf|%16.10lf\n", i, a, b, p, fp);
#endif
        if(fp < 0){
            if(inc) a=p;
            else b=p;
        }
        else{
            if(inc) b=p;
            else a=p;
        }
    }

    return p;
}

double secant(continuous_function f,
    double p0, double p1,
    const double TOL, const int N0
){
    assert(TOL > 0);
    assert(N0 > 0);

    double fp0=f(p0), fp1=f(p1);
    double u0=p0*fp0, u1=p1*fp1;

    double p;

#ifdef SHOW_INTERNAL_PROCESS
    puts("_n|______________pn|___________f(pn)");
#endif
    for(int i=2; i<N0; ++i){
        p = p0 + p1 + (u0-u1) / (fp1-fp0);
        double fp=f(p);

        if((fabs(p1-p0) < TOL) || (fp == 0))
            break;

#ifdef SHOW_INTERNAL_PROCESS
        printf("%2d|%16.10lf|%16.10lf\n", i, p, fp);
#endif
        p0=p1;
        p1=p;
        fp0=fp1;
        fp1=fp;
        u0=u1;
        u1=p*fp;
    }

    return p;
}

double newton(continuous_function f0, derivative f1,
    double x0, double x1,
    const double TOL, const int N0
){
    double p0=(x0 + x1)/2;

    double p;

#ifdef SHOW_INTERNAL_PROCESS
    puts("_n|______________pn|____abs(pn-pn-1)");
    puts(" 0|    0.5000000000|");
#endif
    for(int i=1; i<N0; ++i){
        p = p0 - f0(p0)/f1(p0);
        double fp=f0(p);

        double e=fabs(p-p0);

        if((e < TOL) || (fp == 0))
            break;

#ifdef SHOW_INTERNAL_PROCESS
        printf("%2d|%16.10lf|%16.10lf\n", i, p, e);
#endif

        p0=p;
    }

    return p;
}
