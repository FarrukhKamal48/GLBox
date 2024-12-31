#pragma once

#include <glbpch.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLBox/Events/Event.h"

struct WindowProps
{
    std::string Title;
    unsigned int Width;
    unsigned int Height;

    WindowProps(const std::string& title = "GLBox",
                unsigned int width = 1920,
                unsigned int height = 1080)
        : Title(title), Width(width), Height(height) { }
};

class Window {
public:
    using EventCallbackFn = std::function<void(Event&)>;
    
    Window() = default;
    Window(const WindowProps& props);
    ~Window();

    void Init(const WindowProps& props);
    void OnUpdate();
    void ShutDown();

    void SetEventCallback(EventCallbackFn callback) { m_Data.EventCallback = callback; }

    GLFWwindow* GetWindow()     const { return m_Window; }
    unsigned int GetWidth()     const { return m_Data.Width; }
    unsigned int GetHeight()    const { return m_Data.Height; }
    
private:
    GLFWwindow* m_Window;
    struct WindowData {
        std::string Title;
        unsigned int Width;
        unsigned int Height;
        EventCallbackFn EventCallback;
    };
    WindowData m_Data;
private:
    inline static unsigned int m_GLFWWindowCount = 0;
};
