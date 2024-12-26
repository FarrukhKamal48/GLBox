#pragma once
#include <GLFW/glfw3.h>
#include <string>

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
    Window() = default;
    Window(const WindowProps& props);
    ~Window();

    void OnUpdate();

    GLFWwindow* GetWindow()     const { return m_Window; }
    bool IsClosed()             const { return glfwWindowShouldClose(m_Window); }
    unsigned int GetWidth()     const { return m_Props.Width; }
    unsigned int GetHeight()    const { return m_Props.Height; }
    
    void Init(const WindowProps& props);
    void ShutDown();
private:
    GLFWwindow* m_Window;
    WindowProps m_Props;
private:
    inline static unsigned int m_GLFWWindowCount = 0;
};
