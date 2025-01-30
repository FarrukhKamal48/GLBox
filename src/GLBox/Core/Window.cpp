#include <glbpch.h>

#include "GLBox/Core/Window.h"

#include "GLBox/Events/KeyEvent.h"
#include "GLBox/Events/MouseEvent.h"
#include "GLBox/Events/WindowEvent.h"

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
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;
    
    if (m_GLFWWindowCount == 0) {
        bool succes = glfwInit();
        assert(succes && "glfwInit failed.");
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), 
                                NULL, NULL);
    m_GLFWWindowCount++;
    if (!m_Window) {
        glfwTerminate();
    }
    assert(m_Window != nullptr && "Failed to create window.");

    glfwMakeContextCurrent(m_Window);
    glewInit();
    
    glfwSetWindowUserPointer(m_Window, &m_Data);

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        data.EventCallback(event);
    });
    
    glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow* window, int iconfified){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowMinimizeEvent event(iconfified);
        data.EventCallback(event);
    });
    
    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallback(event);
    });
    
    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        
        switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent event(key, false);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent event(key);
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent event(key, true);
                data.EventCallback(event);
                break;
            }
        }
    });
    
    glfwSetCharCallback(m_Window, [](GLFWwindow* window, uint32_t keycode) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        KeyTypedEvent event(keycode);
        data.EventCallback(event);
    });
    
    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        
        switch (action) {
            case GLFW_PRESS: {
                MousePressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
        }
    });
    
    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double mouseX, double mouseY) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseMovedEvent event(mouseX, mouseY);
        data.EventCallback(event);
    });
    
    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double offsetX, double offsetY) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseScrolledEvent event(offsetX, offsetY);
        data.EventCallback(event);
    });
}

void Window::ShutDown() {
    glfwDestroyWindow(m_Window);
    m_GLFWWindowCount--;

    if (m_GLFWWindowCount == 0) {
        glfwTerminate();
    }
}

