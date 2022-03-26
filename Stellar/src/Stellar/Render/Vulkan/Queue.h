#pragma once

#include <GLFW/glfw3.h>

namespace Stellar {
    class Queue {
    public:
        struct QueueFamilyIndices {
            std::optional<uint32_t> graphicsFamily;

            [[nodiscard]] bool isComplete() const {
                return graphicsFamily.has_value();
            }
        };
    };
}

