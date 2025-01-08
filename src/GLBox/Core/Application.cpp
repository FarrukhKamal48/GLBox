#include <glbpch.h>

#include "GLBox/Core/Application.h"
#include "GLBox/Renderer/Renderer.h"


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
    dispacher.Dispatch<WindowMinimizeEvent>(BIND_EVENT_FN(Application::OnWindowMinimize));
    dispacher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
    
    for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++) {
        if (event.Handled)
            break;
        (*it)->OnEvent(event);
    }
    
    dispacher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
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
    Renderer::BasicBlend();
    Renderer::DepthTest(true);
    
    while (m_Running) {
        double Time = glfwGetTime();
        double deltaTime = Time - m_LastFramTime;
        m_LastFramTime = Time;

        if (!m_Minimized) {
            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate(deltaTime);
                layer->OnRender();
            }
            
            Renderer::DrawAllInstanced();

            m_ImGuiLayer->Begin(); {
                for (Layer* layer : m_LayerStack) {
                    layer->OnImGuiRender();
                }
            }
            m_ImGuiLayer->End();
        }
        m_Window.OnUpdate();
    }
}

bool Application::OnWindowResize(WindowResizeEvent& event) {
    m_Minimized = false;
    Renderer::OnWindowResize(event);
    return false;
}

bool Application::OnWindowMinimize(WindowMinimizeEvent& event) {
    m_Minimized = event.IsMinimized();
    return true;
}

bool Application::OnWindowClose(WindowCloseEvent& event) {
    m_Running = false;
    return true;
}

