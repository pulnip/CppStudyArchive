#include <assert.h>
#include <math.h>
#include <stdio.h>

void secant(double(*f)(double), double p0, double p1,
    const double TOL, const int n0
){
    assert(TOL > 0);
    assert(n0 > 0);

    puts("_n|______________pn|___________f(pn)");
    for(int i=2; i<n0; ++i){
        if(fabs(p1-p0) < TOL)
            break;

        double p = p1 - (f(p1) * (p1-p0)) / (f(p1) - f(p0));
        double fp=f(p);
        printf("%2d|%16.10lf|%16.10lf\n", i, p, fp);

        if(fp == 0)
            break;

        p0=p1;
        p1=p;
    }
}

double f(double x){ return (x+4)*x*x - 10; }

int main(void){
    secant(f, 1, 2, 0.0005, 20);

    return 0;
}
