#include <glbpch.h>
#include "GLBox/Core/Application.h"

#include "GLBox/Renderer/VertexManager.h"
#include "GLBox/Renderer/RenderCommands.h"


Application::Application(const WindowProps& windowProps) {
    assert(s_Instance == nullptr && "Application already exists.");
    s_Instance = this;
    
    m_Window.Init(windowProps);
    m_Window.SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    
    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
}
Application::~Application() { 
}

void Application::OnEvent(Event& event) {
    EventDispacher dispacher(event);
    dispacher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
    dispacher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

    for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++) {
        if (event.Handled)
            break;
        (*it)->OnEvent(event);
    }
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
    
    while (m_Running) {
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

bool Application::OnWindowResize(WindowResizeEvent& event) {
    return true;
}

bool Application::OnWindowClose(WindowCloseEvent& event) {
    m_Running = false;
    return true;
}

