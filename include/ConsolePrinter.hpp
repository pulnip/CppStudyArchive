#pragma once

#include "Printer.hpp"

namespace Project{
    class ConsolePrinter final: public Printer{
      public:
        ConsolePrinter()=default;
        ~ConsolePrinter()=default;

        void print() override;
    };
}
