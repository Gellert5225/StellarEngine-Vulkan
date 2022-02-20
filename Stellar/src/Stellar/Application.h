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

        static const std::vector<const char *> validationLayers;
    private:
        static Application* s_Instance;
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;

        // Vulkan
        VkInstance instance = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
        void initVulkan();
        void setupDebugMessenger();
        static void checkIfExtensionExists(const char**, uint32_t);
        static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT&);
        static bool checkValidationLayerSupport();
        static std::vector<const char*> getRequiredExtensions();
        static VkResult CreateDebugUtilsMessengerEXT(VkInstance,
                                            const VkDebugUtilsMessengerCreateInfoEXT*,
                                            const VkAllocationCallbacks*,
                                            VkDebugUtilsMessengerEXT*);
        static void DestroyDebugUtilsMessengerEXT(VkInstance,
                                                VkDebugUtilsMessengerEXT,
                                                const VkAllocationCallbacks*);
    };

    Application* CreateApplication();
}
