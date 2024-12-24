#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "layer/Input.h"
#include "layer/Renderer.h"
#include "scenes/Scene.h"

extern Scene::Scene* CreateScene();

int main (int argc, char *argv[])
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "GL-out", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    Input::Init(window);
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewInit();

    Scene::Scene* activeScene = CreateScene();
    activeScene->Start();

    double lastTime = glfwGetTime();
    double deltaTime = 0.0;
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* calculate deltaTime */
        lastTime = glfwGetTime();
        if (lastTime < 0) continue;
        
        activeScene->Update(deltaTime);
        activeScene->Render();

        deltaTime = glfwGetTime() - lastTime;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    delete activeScene;
    glfwTerminate();
}
