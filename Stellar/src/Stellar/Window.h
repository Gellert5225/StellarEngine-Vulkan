#pragma once

#include "stlrpch.h"

#include "Core.h"
#include "Events/Event.h"

#include <GLFW/glfw3.h>

#include <utility>

namespace Stellar {
    struct WindowProperty {
        std::string title;
        unsigned int width;
        unsigned int height;

        explicit WindowProperty(std::string  title = "Stellar Engine",
                       unsigned int width = 1280,
                       unsigned int height = 720)
            : title(std::move(title)), width(width), height(height) {}
    };

    class STLR_API Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        explicit Window(const WindowProperty&);
        virtual ~Window();

        virtual void onUpdate();
        [[nodiscard]] virtual unsigned int getWidth() const;
        [[nodiscard]] virtual unsigned int getHeight() const;

        virtual void setEventCallback(const EventCallbackFn& callback);
        virtual void setVsync(bool enabled);
        [[nodiscard]] virtual bool isVsync() const;

        [[nodiscard]] virtual GLFWwindow* getGLFWWindow() const;

        static Window* Create(const WindowProperty& property = WindowProperty());
    private:
        GLFWwindow* m_Window{};

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