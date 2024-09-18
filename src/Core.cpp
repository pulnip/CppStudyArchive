#include "ConsolePrinter.hpp"
#include "Core.hpp"

using namespace std;
using namespace Project;

Core::Core():printer(make_unique<ConsolePrinter>()){}
Core::~Core()=default;

void Core::start(){
    printer->print();
}
