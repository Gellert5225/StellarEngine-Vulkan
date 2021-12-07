#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Stellar {
    class STLR_API Application {
    public:
        Application();
        virtual ~Application();
        void run();
    };
}
