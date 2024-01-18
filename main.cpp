#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sys/types.h>

#include "src/GLlog.h"
#include "src/IndexBuffer.h"
#include "src/VertexBuffer.h"
#include "src/Shader.h"

template <typename T>
T Lerp(T a, T b, T t) {
    return a + (b-a)*t;
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
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewInit();

    {
    
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

    uint vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    VertexBuffer vbuffer(positions, 4 * 2 * sizeof(float));
    
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0));
    GLCall(glEnableVertexAttribArray(0));

    IndexBuffer ibuffer(indices, 6);

    auto shaderPair = GetShaderSource2("assets/shaders/Basic.vert.shader", "assets/shaders/Basic.frag.shader");
    uint program = CreateShader2(shaderPair.vertSrc, shaderPair.fragSrc);
    GLCall(glUseProgram(program));

    GLCall(int u_color = glGetUniformLocation(program, "u_color"));
    GLCall(glUniform4f(u_color, 0.0, 0.5, 1.0, 1.0));
    
    GLCall(glUseProgram(0));
    GLCall(glBindVertexArray(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    float i = 0.1f;
    float r = 1.0f;
    float g = 0.5f;
    float b = 0.7f;
    bool pong = false;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        GLCall(glUseProgram(program));
        GLCall(glUniform4f(u_color, r, g, b, 1.0));

        GLCall(glBindVertexArray(vao));
        ibuffer.Bind();
        
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        
        if (r > 0.95f || r < 0.05f) pong = !pong;
        if (pong) r = Lerp(r, 1.0f, i);
        else      r = Lerp(r, 0.0f, i);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    GLCall(glDeleteProgram(program));
    
    }

    glfwTerminate();
    return 0;
}
