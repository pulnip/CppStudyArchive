#include <exception>
#include <print>

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]){
    try{
        println("Hello, World!");
    }
    catch(const exception& e){
        println("{}", e.what());
    }

    return 0;
}
