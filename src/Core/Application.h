#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Core/LayerStack.h"


class Application {
public:
    Application();
    virtual ~Application();
    
    virtual void PushLayer(Layer* layer);
    virtual void PushOverlay(Layer* layer);
    virtual void Run();

    GLFWwindow* GetWindow() { return m_Window; }

    static Application& Get() { return *s_Instance; }
private:
    GLFWwindow* m_Window;
    LayerStack m_LayerStack;
    double m_LastFramTime = 0.0;
private:
    inline static Application* s_Instance = nullptr;
};
