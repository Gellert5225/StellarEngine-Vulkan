#include "stlrpch.h"
#include "Application.h"

#include "Log.h"

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
        // EventDispatcher diapatcher(e);

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

        while (!glfwWindowShouldClose(m_Window->getGLFWWindow())) {
            for (Layer* layer : m_LayerStack)
                layer->onUpdate();
            m_Window->onUpdate();
        }

        delete VulkanInstance::GetInstance();
    }
}