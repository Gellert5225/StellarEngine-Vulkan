#pragma once

#include "Stellar/Core.h"
#include "VulkanInstance.h"
#include "SwapChain.h"
#include "Queue.h"

#include <GLFW/glfw3.h>

namespace Stellar {
    class STLR_API VulkanDevice {
    private:
        static VulkanDevice* s_Instance;

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice logicalDevice = VK_NULL_HANDLE;

        VkQueue graphicsQueue = VK_NULL_HANDLE;
        VkQueue presentQueue = VK_NULL_HANDLE;

        VkSurfaceKHR* surface = VK_NULL_HANDLE;

        Queue::QueueFamilyIndices m_Indices;

        VulkanDevice() = default;
        bool isDeviceSuitable(VkPhysicalDevice device) const;
        bool checkDeviceExtensionSupport(VkPhysicalDevice device) const;
    public:
        static VulkanDevice* GetInstance();

        void init(VkSurfaceKHR*);
        void pickPhysicalDevice();
        void createLogicalDevice();

        [[nodiscard]] Queue::QueueFamilyIndices getIndices() const;

        VkPhysicalDevice* getPhysicalDevice();
        VkDevice* getLogicalDevice();

        Queue::QueueFamilyIndices findQueueFamilies(VkPhysicalDevice) const;
        SwapChain::SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) const;
        ~VulkanDevice();
    };
}

