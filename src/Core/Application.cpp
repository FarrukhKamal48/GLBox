#include <cassert>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Core/Input.h"
#include "Core/Instancing/VertexManager.h"
#include "Core/Renderer.h"
#include "Core/Application.h"
#include "Core/ImGui/ImGuiLayer.h"


Application::Application(const WindowProps& windowProps) {
    assert(s_Instance == nullptr && "An Application is already running");
    s_Instance = this;
    
    m_Window.Init(windowProps);

    Input::Init(m_Window.GetWindow());
    
    glfwMakeContextCurrent(m_Window.GetWindow());
    glewInit();
    
    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
}
Application::~Application() { 
}

void Application::PushLayer(Layer* layer) {
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer* layer) {
    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
}

void Application::Run() {
    Render::BasicBlend();
    
    while (!m_Window.IsClosed()) {
        double Time = glfwGetTime();
        double deltaTime = Time - m_LastFramTime;
        m_LastFramTime = Time;

        for (Layer* layer : m_LayerStack) {
            layer->Update(deltaTime);
            layer->Render();
        }
        Render::Clear(0.9, 0.9, 0.9, 1);
        Render::DrawAllInstanced();

        m_ImGuiLayer->Begin(); {
            for (Layer* layer : m_LayerStack)
                layer->ImGuiRender();
        }
        m_ImGuiLayer->End();

        m_Window.OnUpdate();
    }
}

