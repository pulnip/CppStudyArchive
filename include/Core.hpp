#pragma once

#include <memory>
#include "fwd.hpp"

namespace Project{
    class Core final{
        std::unique_ptr<Printer> printer;

      public:
        Core();
        ~Core();

        void start();
    };
}
