#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <sys/types.h>
#include "Shader.h"

int main (int argc, char *argv[])
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewInit();

    float positions[6] = {
        0, 0.6f,
        -0.1f, -0.9f,
        0.9f, -0.6f
    };

    uint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);
    glEnableVertexAttribArray(0);

    auto shaderPair = GetShaderSource2("assets/shaders/Basic.vert.shader", "assets/shaders/Basic.frag.shader");
    uint program = CreateShader2(shaderPair.vertSrc, shaderPair.fragSrc);
    glUseProgram(program);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // glDeleteProgram(shader);
    glDeleteProgram(program);

    glfwTerminate();
    return 0;
}
