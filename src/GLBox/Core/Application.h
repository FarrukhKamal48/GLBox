#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLBox/ImGui/ImGuiLayer.h"
#include "GLBox/Core/LayerStack.h"
#include "GLBox/Core/Window.h"

#define WIDTH Application::Get().GetWindow().GetWidth()
#define HEIGHT Application::Get().GetWindow().GetHeight()

class Application {
public:
    Application(const WindowProps& windoProps);
    virtual ~Application();
    
    virtual void PushLayer(Layer* layer);
    virtual void PushOverlay(Layer* layer);

    Window& GetWindow() { return m_Window; }
    static Application& Get() { return *s_Instance; }
private:
    virtual void Run();
private:
    Window m_Window;
    ImGuiLayer* m_ImGuiLayer;
    LayerStack m_LayerStack;
    double m_LastFramTime = 0.0;
private:
    inline static Application* s_Instance = nullptr;
    friend int main(int argc, char** argv);
};
