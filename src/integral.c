#include <math.h>
#include "integral.h"

extern double gaussian(continuous_function f, double a, double b, int n){
    static const double r[][3]={
        {0.5773502692, 0,            0           },
        {0.7745966692, 0.0000000000, 0           },
        {0.8611363116, 0.3399810436, 0           },
        {0.9061798459, 0.5384693101, 0.0000000000}
    };
    static const double c[][3]={
        {1.0000000000, 0           , 0           },
        {0.5555555556, 0.8888888889, 0           },
        {0.3478548451, 0.6521451549, 0           },
        {0.2369268850, 0.4786286705, 0.5688888889}
    };

    double sum=0, mid=(a+b)/2, half=(b-a)/2;
    for(int i=0; i<n; ++i){
        int _i=i<n/2 ? i : n-1-i;
        double x=(i<n/2 ? half : -half)*r[n-2][_i] + mid;
        sum += c[n-2][_i] * f(x);
    }

    return half*sum;
}

double simpson(continuous_function f, double a, double b){
    return (b-a)*(f(a) + 4*f((a+b)/2) + f(b))/6;
}

double adaptive_aux(continuous_function f, double a, double b,
    double s, double TOL
){
    double half=(a+b)/2;
    double left=simpson(f, a, half), right=simpson(f, half, b);

    if(fabs(s - left - right) < 15*TOL)
        return s;

    return adaptive_aux(f, a, half, left, TOL/2)
        + adaptive_aux(f, half, b, right, TOL/2);
}

double adaptive(continuous_function f, double a, double b, double TOL){
    return adaptive_aux(f, a, b, simpson(f, a, b), TOL);
}
