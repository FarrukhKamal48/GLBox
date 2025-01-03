#pragma once

#include <glbpch.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLBox/Events/Event.h"

struct WindowProps
{
    std::string Title;
    uint32_t Width;
    uint32_t Height;

    WindowProps(const std::string& title = "GLBox",
                uint32_t width = 1920,
                uint32_t height = 1080)
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
    uint32_t GetWidth()     const { return m_Data.Width; }
    uint32_t GetHeight()    const { return m_Data.Height; }
    
private:
    GLFWwindow* m_Window;
    struct WindowData {
        std::string Title;
        uint32_t Width;
        uint32_t Height;
        EventCallbackFn EventCallback;
    };
    WindowData m_Data;
private:
    inline static uint32_t m_GLFWWindowCount = 0;
};
