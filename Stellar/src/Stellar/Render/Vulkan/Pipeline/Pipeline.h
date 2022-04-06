#pragma once

#include "Stellar/Core.h"

#include <GLFW/glfw3.h>

namespace Stellar {
    class STLR_API Pipeline {
    public:
        Pipeline() = default;
        virtual ~Pipeline() = 0;

        VkPipeline* getPipeline();
        VkPipelineLayout* getPipelineLayout();

    protected:
        VkPipelineLayout pipelineLayout;
        VkPipeline pipeline;
    };
}