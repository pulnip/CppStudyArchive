#include <math.h>
#include <stdio.h>
#include <time.h>
#include "natest/root_finding.h"

// double LN3;

double f1(double x){ return x*x*x + 4*x*x - 10; }
// double f2(double x){ return x - pow(3, -x); }
// double f2p1(double x){ return 1 + LN3*pow(3, -x); }

int main(void){
    // LN3=log(3);
    // bisection(f1, 1, 2, 0.0005, 20);

    clock_t start=clock();
    for(int i=0; i<1000000; ++i)
        secant_opt(f1, 1, 2, 0.0005, 20);
    clock_t opt_elapsed=clock()-start;

    start=clock();
    for(int i=0; i<1000000; ++i)
        secant(f1, 1, 2, 0.0005, 20);
    clock_t noopt_elapsed=clock()-start;

    printf("%ld %ld\n", noopt_elapsed, opt_elapsed);

    return 0;
}
