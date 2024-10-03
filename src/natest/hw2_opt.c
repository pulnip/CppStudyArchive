#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

void secant(double(*f)(double), double p0, double p1,
    const double TOL, const int n0
){
    assert(TOL > 0);
    assert(n0 > 0);

#ifdef SHOW_INTERNAL_PROCESS
    puts("_n|______________pn|___________f(pn)");
#endif
    for(int i=2; i<n0; ++i){
        if(fabs(p1-p0) < TOL)
            break;

        double p = p1 - (f(p1) * (p1-p0)) / (f(p1) - f(p0));
        double fp=f(p);
#ifdef SHOW_INTERNAL_PROCESS
        printf("%2d|%16.10lf|%16.10lf\n", i, p, fp);
#endif

        if(fp == 0)
            break;

        p0=p1;
        p1=p;
    }
}

void secant_opt(double(*f)(double), double p0, double p1,
    const double TOL, const int n0
){
    assert(TOL > 0);
    assert(n0 > 0);

    double fp0=f(p0), fp1=f(p1);
    double u0=p0*fp0, u1=p1*fp1;

#ifdef SHOW_INTERNAL_PROCESS
    puts("_n|______________pn|___________f(pn)");
#endif
    for(int i=2; i<n0; ++i){
        if(fabs(p1-p0) < TOL)
            break;

        double p = p0 + p1 + (u0-u1) / (fp1-fp0);
        double fp=f(p);
#ifdef SHOW_INTERNAL_PROCESS
        printf("%2d|%16.10lf|%16.10lf\n", i, p, fp);
#endif

        if(fp == 0)
            break;

        p0=p1;
        p1=p;
        fp0=fp1;
        fp1=fp;
        u0=u1;
        u1=p*fp;
    }
}

double f(double x){ return (x+4)*x*x - 10; }

int main(void){
    const int caserun=1000000000;
    // const int caserun=1;

    clock_t case1_start=clock();
    for(volatile int i=0; i<caserun; ++i){
        secant(f, 1, 2, 0.0005, 20);
    }
    clock_t case1=clock()-case1_start;

    clock_t case2_start=clock();
    for(volatile int i=0; i<caserun; ++i){
        secant_opt(f, 1, 2, 0.0005, 20);
    }
    clock_t case2=clock()-case2_start;

    printf("%ld %ld\n", case1, case2);

    return 0;
}
