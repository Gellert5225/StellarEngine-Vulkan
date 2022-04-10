#pragma once

#include <Stellar/Core.h>
#include <vulkan/vulkan.h>

#include "../VulkanImageView.h"

namespace Stellar {
    class STLR_API FrameBuffer {
    public:
        FrameBuffer(VulkanImageView*, VkExtent2D*);
        ~FrameBuffer();

        const std::vector<VkFramebuffer>* getFramebuffers() const;
        size_t getFramebufferSize() const;
    private:
        std::vector<VkFramebuffer> framebuffers;
    };
}