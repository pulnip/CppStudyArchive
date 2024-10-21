#include <cmath>
#include <iostream>
#include "integral.h"

using namespace std;

double f_a(double x){ return exp(2*x)*sin(3*x); }
double f_b(double x){ return exp(3*x)*sin(2*x); }
double f_c(double x){ return 2*x*cos(2*x) - (x-2)*(x-2); }
double f_d(double x){ return 4*x*cos(2*x) - (x-2)*(x-2); }

int main(void){
    const double TOL=0.00001;

    printf("s_1^3(f_a)=%lf, s_1^3(f_b)=%lf, s_0^5(f_c)=%lf, s_0^5(f_d)=%lf\n",
        adaptive_quadrature(f_a, 1, 3, TOL),
        adaptive_quadrature(f_b, 1, 3, TOL),
        adaptive_quadrature(f_c, 0, 5, TOL),
        adaptive_quadrature(f_d, 0, 5, TOL)
    );

    return 0;
}
