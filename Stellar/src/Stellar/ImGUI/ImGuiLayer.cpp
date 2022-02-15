#include "stlrpch.h"
#include "ImGuiLayer.h" 

#include <GLFW/glfw3.h>

#include "Stellar/ImGuiVulkanRenderer.h"
#include "Stellar/Application.h"

namespace Stellar {
    ImGuiLayer::ImGuiLayer() 
        : Layer("ImGuiLayer") {
        
    }

    ImGuiLayer::~ImGuiLayer() {

    }

    void ImGuiLayer::onAttach() {
        // ImGui::CreateContext();
        // ImGui::StyleColorsDark();

        // ImGuiIO& io = ImGui::GetIO();
        // io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        // io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        //ImGui_ImplVulkan_Init();
    }

    void ImGuiLayer::onDetach() {

    }

    void ImGuiLayer::onUpdate() {
        // ImGui_ImplVulkan_NewFrame();
        // ImGui::NewFrame();

        // ImGuiIO& io = ImGui::GetIO();
        // Application& app = Application::Get();
        // io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

        // float time = (float)glfwGetTime();
        // io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);

        // static bool show = true;
        // ImGui::ShowDemoWindow(&show);

        // ImGui::Render();
        //ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::onEvent(Event& e) {

    }
}