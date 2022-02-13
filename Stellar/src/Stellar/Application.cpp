#include "stlrpch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

#include "Stellar/Events/ApplicationEvent.h"
#include "Stellar/Log.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

namespace Stellar {
    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application() {}

    void Application::run() {
        WindowResizeEvent e(1280, 720);
        STLR_INFO(e);

        // HelloTriangleApplication app;
        // app.run();

        while (!glfwWindowShouldClose(m_Window->getGLFWWindow())) {
            m_Window->onUpdate();
        }
    }

    void Application::initVulkan() {
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
                if (!strcmp(glfwExtensions[i], extension.extensionName)){
                    std::cout << extension.extensionName << std::endl;
                    found = true;
                }
            }
            if (!found)
                throw std::runtime_error("Cannot find " + std::string(glfwExtensions[i]));
        }
    }
}