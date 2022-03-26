#pragma once

#include "Stellar/Core.h"
#include "VulkanInstance.h"
#include "Queue.h"

#include <GLFW/glfw3.h>

namespace Stellar {
    class STLR_API VulkanDevice {
    private:
        static VulkanDevice* s_Instance;

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

        VulkanDevice() = default;
        bool isDeviceSuitable(VkPhysicalDevice device);
        uint32_t rateDeviceSuitability(VkPhysicalDevice device);
    public:
        static VulkanDevice* GetInstance();

        void init();
        void pickPhysicalDevice();
        Queue::QueueFamilyIndices findQueueFamilies(VkPhysicalDevice);
        ~VulkanDevice();
    };
}

