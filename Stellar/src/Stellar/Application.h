#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"

namespace Stellar {
    class STLR_API Application {
    public:
        Application();
        virtual ~Application();
        void run();
    };
}

#endif