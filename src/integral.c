#include <math.h>
#include "integral.h"

double simpson(continuous_function f, double a, double b){
    return (b-a)*(f(a) + 4*f((a+b)/2) + f(b))/6;
}

double adaptive_quadrature(continuous_function f, double a, double b, double TOL){
    double result=simpson(f, a, b), h=(a+b)/2;
    double e=fabs(result - simpson(f, a, h) - simpson(f, h, b))/15;

    if(e < TOL)
        return result;

    return adaptive_quadrature(f, a, h, TOL/2) + adaptive_quadrature(f, h, b, TOL/2);
}
