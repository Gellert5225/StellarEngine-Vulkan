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
    };
}