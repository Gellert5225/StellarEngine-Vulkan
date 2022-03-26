#include "stlrpch.h"
#include "VulkanDevice.h"
#include "Stellar/Log.h"

namespace Stellar {
    VulkanDevice* VulkanDevice::s_Instance = nullptr;

    VulkanDevice* VulkanDevice::GetInstance() {
        if (s_Instance == nullptr)
            s_Instance = new VulkanDevice();
        return s_Instance;
    }

    VulkanDevice::~VulkanDevice() {

    }

    void VulkanDevice::init() {
        pickPhysicalDevice();
    }

    void VulkanDevice::pickPhysicalDevice() {
        VkInstance* instance = VulkanInstance::GetInstance()->getVkInstance();
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(*instance, &deviceCount, nullptr);
        if (deviceCount == 0)
            throw std::runtime_error("Failed to find GPUs with Vulkan support");

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(*instance, &deviceCount, devices.data());

        for (const auto& device : devices) {
            if (isDeviceSuitable(device)) {
                physicalDevice = device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }

    bool VulkanDevice::isDeviceSuitable(VkPhysicalDevice device) {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        STLR_CORE_INFO("GPU: {0}", deviceProperties.deviceName);

        Queue::QueueFamilyIndices indices = findQueueFamilies(device);

        return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
                && deviceFeatures.geometryShader && indices.isComplete();
    }

    uint32_t VulkanDevice::rateDeviceSuitability(VkPhysicalDevice device) {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
        uint32_t score = 0;

        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            score += 1000;

        score += deviceProperties.limits.maxImageDimension2D;

        if (!deviceFeatures.geometryShader)
            return 0;

        return score;
    }

    Queue::QueueFamilyIndices VulkanDevice::findQueueFamilies(VkPhysicalDevice device) {
        Queue::QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                indices.graphicsFamily = i;
            if (indices.isComplete())
                break;
            i++;
        }

        return indices;
    }
}