#include <print>
#include "base.hpp"

using namespace std;

TimeGuard::~TimeGuard(){
    chrono::duration<double> elapsed{(Clock::now()-start)};
    println("Elapsed: {}", elapsed.count());
}
