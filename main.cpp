#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "src/scenes/SceneCircle.h"
#include "src/scenes/SceneClearColor.h"
#include "src/scenes/SceneVerlet.h"

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
    window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewInit();

    Scene::Verlet verletScene;
    verletScene.Start();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        verletScene.Update(0);
        verletScene.Render();
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}
