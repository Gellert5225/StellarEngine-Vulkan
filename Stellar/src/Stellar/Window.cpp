#include "stlrpch.h"
#include "Window.h"

#include "Stellar/Events/ApplicationEvent.h"
#include "Stellar/Events/MouseEvent.h"
#include "Stellar/Events/KeyEvent.h"

namespace Stellar {
    Window* Window::Create(const WindowProperty& property) {
        return new Window(property);
    }

    Window::Window(const WindowProperty& property) {
        init(property);
    }

    void Window::init(const WindowProperty& property) {
        
    }

    void Window::shutDown() {
        glfwDestroyWindow(m_Window);
    }

    Window::~Window() {
        shutDown();
    }
}