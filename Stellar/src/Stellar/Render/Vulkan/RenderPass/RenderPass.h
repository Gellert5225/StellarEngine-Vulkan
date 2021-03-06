#pragma once
#include "Stellar/Core.h"

#include <vulkan/vulkan.h>

namespace Stellar {
    class STLR_API RenderPass {
    public:
        RenderPass() = default;
        virtual ~RenderPass() = 0;

        VkRenderPass* getVkRenderPass();
    protected:
        VkRenderPass renderPass;
    };
}