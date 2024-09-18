#include <exception>
#include <print>
#include "Core.hpp"

using namespace std;
using namespace Project;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]){
    try{
        Core core{};
        core.start();
    }
    catch(const exception& e){
        println("{}", e.what());
    }

    return 0;
}
