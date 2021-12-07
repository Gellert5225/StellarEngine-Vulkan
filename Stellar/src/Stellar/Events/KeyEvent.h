#pragma once

#include "Event.h"

namespace Stellar {
    class STLR_API KeyEvent : public Event {
    public:
        inline int getKeyCode() const { return m_KeyCode; }
        EVENT_CLASS_CATEGORY(Keyboard | Input)
    protected:
        KeyEvent(int keyCode)
            : m_KeyCode(keyCode) {}
        int m_KeyCode;
    };

    class STLR_API KeyPressedEvent : public KeyEvent {
        KeyPressedEvent(int keyCode, int repeatCount)
            : KeyEvent(keyCode), m_RepeatCount(repeatCount) {}
        inline int getRepeatCount() const { return m_RepeatCount; }
        std::string toString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }
        EVENT_CLASS_TYPE(KeyPressed)
    private:
        int m_RepeatCount;
    };

    class STLR_API KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(int keyCode)
            : KeyEvent(keyCode) {}

        std::string toString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}