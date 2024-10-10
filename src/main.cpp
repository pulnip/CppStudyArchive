#include <exception>
#include <iostream>

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]){
    try{
        puts("Hello, World!");
    }
    catch(const exception& e){
        printf("%s\n", e.what());
    }

    return 0;
}
