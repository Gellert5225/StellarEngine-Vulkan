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
        VkDebugUtilsMessengerEXT debugMessenger;
        void initVulkan();
        void checkIfExtensionExists(const char**, const uint32_t) const;
        void setupDebugMessenger();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT&);
        bool checkValidationLayerSupport() const;
        std::vector<const char*> getRequiredExtensions() const;
        VkResult CreateDebugUtilsMessengerEXT(VkInstance, 
                                            const VkDebugUtilsMessengerCreateInfoEXT*, 
                                            const VkAllocationCallbacks*, 
                                            VkDebugUtilsMessengerEXT*);
        static void DestroyDebugUtilsMessengerEXT(VkInstance, VkDebugUtilsMessengerEXT, const VkAllocationCallbacks*);
    };

    Application* CreateApplication();
}
