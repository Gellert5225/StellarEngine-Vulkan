#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Stellar {
    class STLR_API Layer {
    public: 
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate() {}
        virtual void onEvent(Event& e) {}

        inline const std::string& getName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };
}