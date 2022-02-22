#pragma once

#include "Stellar/Core.h"
#include "VulkanValidationLayer.h"

#include <GLFW/glfw3.h>

namespace Stellar {
    class VulkanValidationLayer;

    class STLR_API VulkanInstance {
    public:
        void init(const std::string&,
                  int,
                  const std::string&,
                  int);

        ~VulkanInstance();
        static VulkanInstance* GetInstance();
        void createVkInstance(const std::string&,
                              int,
                              const std::string&,
                              int);
        VkInstance* getVkInstance();

        VulkanValidationLayer* getValidationLayerManager() const;

    private:
        static VulkanInstance* s_Instance;

        static void CheckIfExtensionExists(const char**, uint32_t);
        static std::vector<const char*> GetRequiredExtensions();

        VkInstance vkInstance = VK_NULL_HANDLE;
        VulkanValidationLayer* validationLayerManager = nullptr;
        VulkanInstance() = default;
    };
}
