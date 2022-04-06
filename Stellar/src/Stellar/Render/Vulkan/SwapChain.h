#pragma once

#include "Stellar/Core.h"

#include <GLFW/glfw3.h>

namespace Stellar {
    class STLR_API SwapChain {
    public:
        struct SwapChainSupportDetails {
            VkSurfaceCapabilitiesKHR capabilities;
            std::vector<VkSurfaceFormatKHR> formats;
            std::vector<VkPresentModeKHR> presentModes;
        };

    public:
        SwapChain();
        ~SwapChain();

        [[nodiscard]] const std::vector<VkImage>* getSwapChainImages() const;
        [[nodiscard]] VkFormat getSwapChainImageFormat() const;
        [[nodiscard]] VkExtent2D getSwapChainExtent() const;


        [[nodiscard]] static VkSurfaceFormatKHR chooseSwapSurfaceFormat(
                const std::vector<VkSurfaceFormatKHR>&);
        [[nodiscard]] static VkPresentModeKHR chooseSwapPresentMode(
                const std::vector<VkPresentModeKHR>&);
        [[nodiscard]] static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR&);

    private:
        VkSwapchainKHR vkSwapChain = VK_NULL_HANDLE;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
    };
}