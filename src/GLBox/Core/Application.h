#pragma once

#include "GLBox/Core/Window.h"
#include "GLBox/Core/LayerStack.h"
#include "GLBox/Events/Event.h"
#include "GLBox/Events/WindowEvent.h"

#include "GLBox/ImGui/ImGuiLayer.h"

class Application {
public:
    Application(const WindowProps& windoProps);
    virtual ~Application();

    void OnEvent(Event& event);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

    Window& GetWindow() { return m_Window; }
    ImGuiLayer& GetImGuiLayer() { return *m_ImGuiLayer; }
    static Application& Get() { return *s_Instance; }
private:
    virtual void Run();
    virtual bool OnWindowResize(WindowResizeEvent& event);
    virtual bool OnWindowMinimize(WindowMinimizeEvent& event);
    virtual bool OnWindowClose(WindowCloseEvent& event);
private:
    Window m_Window;
    ImGuiLayer* m_ImGuiLayer;
    LayerStack m_LayerStack;
    double m_LastFramTime = 0.0;
    bool m_Running = true;
    bool m_Minimized = false;
private:
    inline static Application* s_Instance = nullptr;
    friend int main(int argc, char** argv);
};
