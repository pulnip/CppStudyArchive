#include <exception>
#include <print>
#include "fwd.hpp"

using namespace std;
using namespace cvtest;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]){
    try{
        // drawLine();
        simple_videoplayer();
    }
    catch(const exception& e){
        println("{}", e.what());
    }

    return 0;
}
