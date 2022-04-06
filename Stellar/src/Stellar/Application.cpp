#include "stlrpch.h"
#include "Application.h"

#include "Log.h"

#include <filesystem>
#include <unistd.h>

namespace Stellar {
    #define BIND_EVENT_FN(X) std::bind(&X, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        STLR_CORE_ASSERT(!s_Instance, "Application already exists")
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->setEventCallback(BIND_EVENT_FN(Application::onEvent));
    }

    Application::~Application() = default;

    void Application::onEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            (*--it)->onEvent(e);
            if (e.handled)
                break;
        }
    }

    void Application::pushLayer(Layer* layer) {
        m_LayerStack.pushLayer(layer);
    }

    void Application::pushOverlay(Layer* layer) {
        m_LayerStack.pushOverlay(layer);
    }

    void Application::run() {
        VulkanInstance::GetInstance()->init("Stellar Engine Sandbox", 1, "Stellar", 1);
        VulkanSurface::GetInstance()->init(m_Window->getGLFWWindow());
        VulkanDevice::GetInstance()->init(VulkanSurface::GetInstance()->getSurface());
        VulkanDevice::GetInstance()->createLogicalDevice();
        SwapChain* swapChain = new SwapChain();
        VulkanImageView* imageView = new VulkanImageView(swapChain);
        GraphicsPipeline* pipeline = new GraphicsPipeline("resource/Shader/shaderVert.spv",
                                                          "resource/Shader/shaderFrag.spv");


        while (m_Running) {
            for (Layer* layer : m_LayerStack)
                layer->onUpdate();
            m_Window->onUpdate();
        }

        delete imageView;
        delete swapChain;
        delete VulkanDevice::GetInstance();
        delete VulkanSurface::GetInstance();
        delete VulkanInstance::GetInstance();
        m_Window = nullptr;
    }

    bool Application::onWindowClose(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }
}