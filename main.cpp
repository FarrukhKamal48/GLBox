#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "src/layer/Input.h"
#include "src/scenes/VerletInstancing.scene.h"

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double mouseX = 0;
    double mouseY = 0;
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        glfwGetCursorPos(window, &mouseX, &mouseY);
        std::cout << mouseX << ", " << mouseY << "\n";
    }
}

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

    Scene::VerletInstanced activeScene;
    activeScene.Start();

    double lastTime = glfwGetTime();
    double deltaTime = 0.0;
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        lastTime = glfwGetTime();
        if (lastTime < 0) continue;
        
        activeScene.Update(deltaTime);
        activeScene.Render();

        deltaTime = glfwGetTime() - lastTime;
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // delete activeScene;

    glfwTerminate();
    return 0;
}
