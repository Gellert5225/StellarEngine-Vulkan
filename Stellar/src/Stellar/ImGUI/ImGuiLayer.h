#pragma once

#include "Stellar/Layer.h"

namespace Stellar {
    class STLR_API ImGuiLayer: public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void onAttach();
        void onDetach();
        void onUpdate();
        void onEvent(Event& e);
    private:
        float m_Time = 0.0f;
    };
}