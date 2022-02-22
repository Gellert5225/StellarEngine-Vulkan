#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

#include "Render/Vulkan/VulkanInstance.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

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
        bool m_Running = true;
        LayerStack m_LayerStack;

        // Vulkan
        VkInstance instance = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
    };

    Application* CreateApplication();
}
