#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

namespace Stellar {
    class STLR_API Application {
    public:
        Application();
        virtual ~Application();

        void run();
        void onEvent(Event&);

        void pushLayer(Layer*);
        void pushOverlay(Layer*);

        inline static Application& Get() { return *s_Instance; }
        inline Window& getWindow() { return *m_Window; }
    private:
        static Application* s_Instance;

        std::unique_ptr<Window> m_Window;
        VkInstance instance;
        bool m_Running = true;
        LayerStack m_LayerStack;

        // Vulkan
        void initVulkan();
        void checkIfExtensionExists(const char**, const uint32_t) const;
    };

    Application* CreateApplication();
}
