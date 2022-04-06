#include "stlrpch.h"
#include "RenderPass.h"

#include "../VulkanDevice.h"

namespace Stellar {
    RenderPass::~RenderPass() {
        vkDestroyRenderPass(*VulkanDevice::GetInstance()->getLogicalDevice(), renderPass, nullptr);
    }

    VkRenderPass* RenderPass::getVkRenderPass() {
        return &renderPass;
    }
}
