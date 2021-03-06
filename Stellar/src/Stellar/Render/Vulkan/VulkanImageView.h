#pragma once

#include "Stellar/Core.h"
#include "SwapChain.h"

#include <vulkan/vulkan.h>

namespace Stellar {
    class STLR_API VulkanImageView {
    private:
        std::vector<VkImageView> swapChainImageViews;
    public:
        explicit VulkanImageView(SwapChain*);
        ~VulkanImageView();

        [[nodiscard]] const std::vector<VkImageView>* getSwapChainImageViews() const;
    };
}