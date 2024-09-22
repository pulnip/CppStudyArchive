#include <math.h>
#include "natest/root_finding.h"

double LN3;

double f1(double x){ return x*x*x + 4*x*x - 10; }
double f2(double x){ return x - pow(3, -x); }
double f2p1(double x){ return 1 + LN3*pow(3, -x); }

int main(void){
    LN3=log(3);
    bisection(f1, 1, 2, 0.0005, 20);

    return 0;
}
