#include "stlrpch.h"
#include "VulkanInstance.h"

#include "Stellar/Log.h"

namespace Stellar {
    VulkanInstance* VulkanInstance::s_Instance = nullptr;

    void VulkanInstance::init(const std::string& appName,
                              int appVersion,
                              const std::string& engineName,
                              int engineVersion) {
        if (VulkanValidationLayer::ValidationLayerEnabled())
            validationLayerManager = new VulkanValidationLayer();

        createVkInstance(appName, appVersion, engineName, engineVersion);

        if (validationLayerManager)
            validationLayerManager->setupDebugMessenger();
    }

    VulkanInstance::~VulkanInstance() {
        delete validationLayerManager;
        vkDestroyInstance(vkInstance, nullptr);
    }

    VulkanInstance *VulkanInstance::GetInstance() {
        if (s_Instance == nullptr)
            s_Instance = new VulkanInstance();
        return s_Instance;
    }

    void VulkanInstance::createVkInstance(const std::string& appName,
                                          int appVersion,
                                          const std::string& engineName,
                                          int engineVersion) {
        STLR_CORE_INFO("Initializing Vulkan");
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = appName.c_str();
        appInfo.applicationVersion = appVersion;
        appInfo.pEngineName = engineName.c_str();
        appInfo.engineVersion = engineVersion;
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

        CheckIfExtensionExists(glfwExtensions, glfwExtensionCount);

        auto extensions = GetRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
#ifndef NDEBUG
        createInfo.enabledLayerCount = static_cast<uint32_t>(VulkanValidationLayer::GetValidationLayers().size());
        createInfo.ppEnabledLayerNames = VulkanValidationLayer::GetValidationLayers().data();
        VulkanValidationLayer::PopulateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
#else
        createInfo.enabledLayerCount = 0;

        createInfo.pNext = nullptr;
#endif

        if (vkCreateInstance(&createInfo, nullptr, &vkInstance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
    }

    void VulkanInstance::CheckIfExtensionExists(const char** glfwExtensions,
                                uint32_t glfwExtensionCount) {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        for (uint32_t i = 0; i < glfwExtensionCount; i++) {
            bool found = false;
            for (const auto& extension : extensions) {
                if (!strcmp(glfwExtensions[i], extension.extensionName))
                    found = true;
            }
            if (!found)
                throw std::runtime_error("Cannot find " + std::string(glfwExtensions[i]));
        }
    }

    std::vector<const char *> VulkanInstance::GetRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifndef NDEBUG
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

        return extensions;
    }

    VkInstance *VulkanInstance::getVkInstance() {
        return &vkInstance;
    }
}