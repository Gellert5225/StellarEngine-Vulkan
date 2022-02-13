#include "stlrpch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

#include "Log.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

namespace Stellar {
    #define BIND_EVENT_FN(X) std::bind(&X, this, std::placeholders::_1)

    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->setEventCallback(BIND_EVENT_FN(Application::onEvent));
    }

    Application::~Application() {}

    void Application::onEvent(Event& e) {
        EventDispatcher diapatcher(e);

        // STLR_CORE_TRACE("{0}", e);

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            (*--it)->onEvent(e);
            if (e.handled)
                break;
        }
    }

    void Application::pushLayer(Layer* layer) {
        m_LayerStack.pushLayer(layer);
    }

    void Application::pushOverlay(Layer* layer) {
        m_LayerStack.pushOverlay(layer);
    }

    void Application::run() {
        initVulkan();

        while (!glfwWindowShouldClose(m_Window->getGLFWWindow())) {
            for (Layer* layer : m_LayerStack)
                layer->onUpdate();
            m_Window->onUpdate();
        }
    }

    void Application::initVulkan() {
        STLR_CORE_INFO("Initializing Vulkan");
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Stellar Engine Sandbox";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Stellar";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create Vulkan instance!");
        }
        checkIfExtensionExists(glfwExtensions, glfwExtensionCount);
    }

    void Application::checkIfExtensionExists(const char** glfwExtensions, 
                                            const uint32_t glfwExtensionCount) const {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        for (uint32_t i = 0; i < glfwExtensionCount; i++) {
            bool found = false;
            for (const auto& extension : extensions) {
                STLR_CORE_INFO("Extension found: {0}", extension.extensionName);
                if (!strcmp(glfwExtensions[i], extension.extensionName))
                    found = true;
            }
            if (!found)
                throw std::runtime_error("Cannot find " + std::string(glfwExtensions[i]));
        }
    }
}