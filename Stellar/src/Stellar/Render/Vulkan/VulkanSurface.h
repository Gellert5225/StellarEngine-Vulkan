#pragma once

#include "Stellar/Core.h"
#include "Stellar/Window.h"

#include <GLFW/glfw3.h>

namespace Stellar {
    class STLR_API VulkanSurface {
    public:
        static VulkanSurface* GetInstance();
        void init(GLFWwindow*);
        ~VulkanSurface();
        void createSurface(GLFWwindow*);
        VkSurfaceKHR* getSurface();
    private:
        static VulkanSurface* s_Instance;
        VkSurfaceKHR surface;
        VulkanSurface() = default;
    };
}
