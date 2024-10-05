#include <time.h>
#include <exception>
#include <print>
#include "root_finding.h"

using namespace std;

double f(double x){ return (x+4)*x*x - 10; }

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]){

    // const int caserun=1000000000;
    const int caserun=1;

    try{
        clock_t case1_start=clock();
        for(volatile int i=0; i<caserun; ++i){
            secant(f, 1, 2, 0.0005, 20);
        }
    clock_t case1=clock()-case1_start;
    }
    catch(const exception& e){

        println("{}", e.what());
    }

    return 0;
}
