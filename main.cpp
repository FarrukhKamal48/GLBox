#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "src/GLlog.h"

#include "src/IndexBuffer.h"
#include "src/VertexBuffer.h"
#include "src/VertexArray.h"

#include "src/Renderer.h"
#include "src/Shader.h"
#include "src/Texture.h"

#include "src/vendor/glm/common.hpp"
#include "src/vendor/glm/ext/matrix_transform.hpp"
#include "src/vendor/glm/fwd.hpp"
#include "src/vendor/glm/glm.hpp"
#include "src/vendor/glm/gtc/matrix_transform.hpp"

#define WIDTH (float)1920
#define HEIGHT (float)1080

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
    window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewInit();

    float positions[4*4] = {
        -100.0f, -100.0f, 0.0f, 0.0f,
         100.0f, -100.0f, 1.0f, 0.0f,
         100.0f,  100.0f, 1.0f, 1.0f,
        -100.0f,  100.0f, 0.0f, 1.0f,
    };
    unsigned int indices[4*2] = {
        0, 1, 2, 
        0, 2, 3
    };
    
    Renderer renderer;
    renderer.BasicBlend();

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(WIDTH/2+300, HEIGHT-100, 0.0f));
    glm::mat4 mvp = proj * view * model;
    
    Shader shader;
    shader.Push(GL_VERTEX_SHADER, "assets/shaders/Basic.vert");
    shader.Push(GL_FRAGMENT_SHADER, "assets/shaders/Basic.frag");
    shader.Compile();
    shader.Bind();
    shader.SetUniformVec4("u_color", 0.0f, 0.5f, 1.0f, 1.0f);
    shader.SetUniformMat4("u_MVP", mvp);
    shader.SetUniformVec2("u_Offset", 0.0f, 0.0f);

    Texture texture("assets/textures/tes_1000x1000px.png");
    texture.Bind();
    shader.SetUniform("u_Texture", texture.GetSlot());
    
    shader.UnBind();
    va.UnBind();
    vb.UnBind();
    ib.UnBind();

    
    glm::vec2 centre(WIDTH/2, HEIGHT/2);
    float Radius = HEIGHT/2;
    glm::vec2 displacment;
    glm::vec2 pos(WIDTH/2 + Radius-100, HEIGHT/2);
    glm::vec2 vel(0, 0);
    glm::vec2 acc(0, -5);

       /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear(1, 1, 1, 1);

        renderer.Draw(va, ib, shader);
        
        // firstScene.Update(0);
        // firstScene.Render();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0));
        glm::mat4 mvp = proj * view * model;
        shader.Bind();
        shader.SetUniformMat4("u_MVP", mvp);

        pos += vel;
        vel += acc;

        displacment = pos - centre;
        float dist = glm::length(displacment);

        if (dist > Radius - 100) {
            pos = centre + (displacment/dist * (Radius - 100));
        }
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}
