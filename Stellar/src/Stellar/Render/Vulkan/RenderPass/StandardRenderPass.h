#pragma once

#include "Stellar/Core.h"

#include "RenderPass.h"

namespace Stellar {
    class STLR_API StandardRenderPass : public RenderPass {
    public:
        static StandardRenderPass* GetInstance();

        void init(const VkFormat&);

        ~StandardRenderPass() override = default;
    private:
        static StandardRenderPass* s_Instance;
        StandardRenderPass() = default;
    };
}