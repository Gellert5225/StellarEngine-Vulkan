#include "VulkanImageView.h"
#include "VulkanDevice.h"

#include "Stellar/Log.h"

namespace Stellar {

    VulkanImageView::VulkanImageView(SwapChain* swapChain) {
        swapChainImageViews.resize(swapChain->getSwapChainImages()->size());

        for (size_t i = 0; i < swapChain->getSwapChainImages()->size(); i++) {
            VkImageViewCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image = (*swapChain->getSwapChainImages())[i];
            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;
            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.format = swapChain->getSwapChainImageFormat();

            if (vkCreateImageView(*VulkanDevice::GetInstance()->getLogicalDevice(),
                                  &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create image views!");
            }
        }
    }

    VulkanImageView::~VulkanImageView() {
        for (auto imageView : swapChainImageViews)
            vkDestroyImageView(*VulkanDevice::GetInstance()->getLogicalDevice(),
                               imageView, nullptr);
    }

    const std::vector<VkImageView>* VulkanImageView::getSwapChainImageViews() const {
        return &swapChainImageViews;
    }
}