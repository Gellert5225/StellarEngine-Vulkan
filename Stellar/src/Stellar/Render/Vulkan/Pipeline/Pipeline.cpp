#include "stlrpch.h"
#include "Pipeline.h"

namespace Stellar {
    Pipeline::~Pipeline() {

    }

    VkPipeline* Pipeline::getPipeline() {
        return &pipeline;
    }

    VkPipelineLayout* Pipeline::getPipelineLayout() {
        return &pipelineLayout;
    }
}