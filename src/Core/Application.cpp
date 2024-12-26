#include <cassert>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Core/Application.h"
#include "Core/Input.h"
#include "Core/Instancing/VertexManager.h"
#include "Core/Renderer.h"


Application::Application() {
    assert(s_Instance == nullptr);
    s_Instance = this;

    /* Initialize the library */
    if (!glfwInit())
        std::exit(1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    m_Window = glfwCreateWindow(WIDTH, HEIGHT, "GL-out", NULL, NULL);
    if (!m_Window) {
        glfwTerminate();
        std::exit(1);
    }

    Input::Init(m_Window);
    
    /* Make the window's context current */
    glfwMakeContextCurrent(m_Window);

    glewInit();
}
Application::~Application() { 
    glfwTerminate();
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
    
    while (!glfwWindowShouldClose(m_Window)) {
        double Time = glfwGetTime();
        double deltaTime = Time - m_LastFramTime;
        m_LastFramTime = Time;

        
        for (Layer* layer : m_LayerStack) {
            layer->Update(deltaTime);
            layer->Render();
        }
        
        Render::Clear(0.9, 0.9, 0.9, 1);
        Render::DrawAllInstanced();

        /* Swap front and back buffers */
        glfwSwapBuffers(m_Window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

