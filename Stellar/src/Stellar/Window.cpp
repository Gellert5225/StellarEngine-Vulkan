#include "stlrpch.h"
#include "Window.h"
#include "Log.h"

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
        m_Data.Title = property.title;
        m_Data.Width = property.width;
        m_Data.Height = property.height;

        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        STLR_CORE_INFO("Creating window {0} ({1}, {2})", 
            property.title, property.width, property.height);

        m_Window = glfwCreateWindow(property.width, 
            property.height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        setVsync(true);
    }

    unsigned int Window::getHeight() const {
        return m_Data.Height;
    }

    unsigned int Window::getWidth() const {
        return m_Data.Width;
    }

    GLFWwindow* Window::getGLFWWindow() const {
        return m_Window;
    }

    void Window::setEventCallback(const EventCallbackFn& callback) {
        m_Data.EventCallback = callback;
    }

    void Window::onUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void Window::setVsync(bool enabled) {
        if (enabled)
            glfwSwapInterval(1);
        else 
            glfwSwapInterval(0);
        m_Data.VSync = enabled;
    }

    bool Window::isVsync() const {
        return m_Data.VSync;
    }

    void Window::shutDown() {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    Window::~Window() {
        shutDown();
    }
}