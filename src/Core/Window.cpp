#include <cassert>
#include "Core/Window.h"

Window::Window(const WindowProps& props) {
    Init(props);
}
Window::~Window() {
    ShutDown();
}

void Window::OnUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

void Window::Init(const WindowProps& props) {
    m_Props = props;
    
    if (m_GLFWWindowCount == 0) {
        bool succes = glfwInit();
        assert(succes && "glfwInit failed.");
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    m_Window = glfwCreateWindow(m_Props.Width, m_Props.Height, m_Props.Title.c_str(), 
                                NULL, NULL);
    if (!m_Window) {
        glfwTerminate();
    }
    assert(m_Window != nullptr && "Failed to create window.");
    
    m_GLFWWindowCount++;
    glfwSetWindowUserPointer(m_Window, &m_Props);
}

void Window::ShutDown() {
    glfwDestroyWindow(m_Window);
    m_GLFWWindowCount--;

    if (m_GLFWWindowCount == 0) {
        glfwTerminate();
    }
}

