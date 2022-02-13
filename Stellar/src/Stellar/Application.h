#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"

namespace Stellar {
    class STLR_API Application {
    public:
        Application();
        virtual ~Application();
        void run();
    private:
        std::unique_ptr<Window> m_Window;
        VkInstance instance;
        bool m_Running = true;

        void initVulkan();
        void checkIfExtensionExists(const char**, const uint32_t) const;
    };

    Application* CreateApplication();
}
