#include "stlrpch.h"
#include "Pipeline.h"
#include "../VulkanDevice.h"

namespace Stellar {
    Pipeline::~Pipeline() {
        vkDestroyPipeline(*VulkanDevice::GetInstance()->getLogicalDevice(), pipeline, nullptr);
        vkDestroyPipelineLayout(*VulkanDevice::GetInstance()->getLogicalDevice(),
                                pipelineLayout, nullptr);
    }

    VkPipeline* Pipeline::getPipeline() {
        return &pipeline;
    }

    VkPipelineLayout* Pipeline::getPipelineLayout() {
        return &pipelineLayout;
    }
}