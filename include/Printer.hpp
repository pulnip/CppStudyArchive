#pragma once

namespace Project{
    class Printer{
      public:
        Printer()=default;
        virtual ~Printer()=default;

        virtual void print()=0;
    };
}
