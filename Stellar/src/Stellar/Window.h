#pragma once

#include "stlrpch.h"

#include "Stellar/Core.h"
#include "Stellar/Events/Event.h"

#include <GLFW/glfw3.h>

namespace Stellar {
    struct WindowProperty {
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProperty(const std::string& title = "Stellar Engine",
                       unsigned int width = 1280,
                       unsigned int height = 720)
            : title(title), width(width), height(height) {}
    };

    class STLR_API Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        Window(const WindowProperty&);
        virtual ~Window();

        virtual void onUpdate();
        virtual unsigned int getWidth() const;
        virtual unsigned int getHeight() const;

        virtual void setEventCallback(const EventCallbackFn& callback);
        virtual void setVsync(bool enabled);
        virtual bool isVsync() const;

        virtual GLFWwindow* getGLFWWindow() const;

        static Window* Create(const WindowProperty& property = WindowProperty());
    private:
        GLFWwindow* m_Window;

        struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};
        WindowData m_Data;

    private:
        virtual void init(const WindowProperty& property);
        virtual void shutDown();
    };
}