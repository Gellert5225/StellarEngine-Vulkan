#pragma once

#include "Stellar/Core.h"
#include "VulkanInstance.h"

#include <GLFW/glfw3.h>

namespace Stellar {
    class STLR_API VulkanDevice {
    private:
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

        VulkanDevice() = default;
        bool isDeviceSuitable(VkPhysicalDevice device);
        uint32_t rateDeviceSuitability(VkPhysicalDevice device);
    public:
        void pickPhysicalDevice();

    };
}

