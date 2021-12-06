#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"

namespace STLR_API Stellar {
    class Application {
    public:
        Application();
        virtual ~Application();
        void run();
    };
}

#endif