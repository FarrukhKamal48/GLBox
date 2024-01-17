#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sys/types.h>

#include "Shader.h"
#include "GLlog.cpp"

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

    float positions[4*2] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };
    uint indices[4*2] = {
        0, 1, 2, 
        0, 2, 3
    };

    uint buffer;
    GLCall(glGenBuffers(1, &buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0));
    GLCall(glEnableVertexAttribArray(0));

    uint ibo;
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint), indices, GL_STATIC_DRAW));

    auto shaderPair = GetShaderSource2("assets/shaders/Basic.vert.shader", "assets/shaders/Basic.frag.shader");
    uint program = CreateShader2(shaderPair.vertSrc, shaderPair.fragSrc);
    glUseProgram(program);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // glDeleteProgram(shader);
    GLCall(glDeleteProgram(program));

    glfwTerminate();
    return 0;
}
