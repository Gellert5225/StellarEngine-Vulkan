#include "stlrpch.h"
#include "GraphicsPipeline.h"

#include "../VulkanDevice.h"

namespace Stellar {

    GraphicsPipeline::GraphicsPipeline(const std::string& vertShaderPath,
                                       const std::string& fragShaderPath) {
        VkShaderModule vertShaderModule = Shader::GetInstance()->getShaderModule(vertShaderPath);
        VkShaderModule fragShaderModule = Shader::GetInstance()->getShaderModule(fragShaderPath);

        VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertShaderStageInfo.module = vertShaderModule;
        vertShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragShaderStageInfo.module = fragShaderModule;
        fragShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

        vkDestroyShaderModule(*VulkanDevice::GetInstance()->getLogicalDevice(),
                              fragShaderModule, nullptr);
        vkDestroyShaderModule(*VulkanDevice::GetInstance()->getLogicalDevice(),
                              vertShaderModule, nullptr);
    }
}