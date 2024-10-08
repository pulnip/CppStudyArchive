#include <cmath>
#include <ctime>
#include <iostream>
#include "root_finding.h"

using namespace std;

double f1(double x){ return (x+4)*x*x - 10; }

double f2(double x){ return x-pow(3, -x); }
double f2_derived(double x){ return 1+log(3)*pow(3, -x); }

int main(void){
#ifdef OPTIMIZATION_TEST
    const int caserun=1000000000;
#endif

#ifdef OPTIMIZATION_TEST
    clock_t start=clock();
    for(volatile int i=0; i<caserun; ++i){
#endif
    // bisection(f1, 1, 2, 0.0005, 20);
    // secant(f1, 1, 2, 0.0005, 20);
    newton(f2, f2_derived, 0, 1, 0.00000001, 20);
#ifdef OPTIMIZATION_TEST
    }
    clock_t elapsed=clock()-start;
    printf("{}ms", elapsed);
#endif

    return 0;
}
