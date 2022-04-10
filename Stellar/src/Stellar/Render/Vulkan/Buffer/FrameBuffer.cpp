#include "stlrpch.h"
#include "FrameBuffer.h"

#include "../RenderPass/StandardRenderPass.h"
#include "../VulkanDevice.h"

namespace Stellar {

    FrameBuffer::FrameBuffer(VulkanImageView* vulkanImageView, VkExtent2D* swapChainExtent) {
        auto swapChainImageViews = vulkanImageView->getSwapChainImageViews();
        framebuffers.resize(swapChainImageViews->size());

        for (size_t i = 0; i < swapChainImageViews->size(); i++) {
            VkImageView attachments[] = {
                    (*swapChainImageViews)[i]
            };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = *StandardRenderPass::GetInstance()->getVkRenderPass();
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.pAttachments = attachments;
            framebufferInfo.width = swapChainExtent->width;
            framebufferInfo.height = swapChainExtent->height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(*VulkanDevice::GetInstance()->getLogicalDevice(),
                    &framebufferInfo, nullptr, &framebuffers[i]) != VK_SUCCESS)
                throw std::runtime_error("Failed to create framebuffer");
        }
    }

    FrameBuffer::~FrameBuffer() {
        for (auto framebuffer: framebuffers)
            vkDestroyFramebuffer(*VulkanDevice::GetInstance()->getLogicalDevice(),
                                 framebuffer, nullptr);
    }
}