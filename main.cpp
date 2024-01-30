#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "src/IndexBuffer.h"
#include "src/VertexBuffer.h"
#include "src/VertexArray.h"

#include "src/Renderer.h"
#include "src/Shader.h"
#include "src/Texture.h"

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
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(WIDTH/2, HEIGHT/2, 0.0f));
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

    float i = 0.1f;
    float r = 1.0f;
    float g = 0.5f;
    float b = 0.7f;
    bool pong = false;

    glm::vec3 offset(WIDTH/2, HEIGHT/2, 0.0f);
    float x = 10.0f;
    float y = 10.0f;
//
       /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();
        
        shader.Bind();
        shader.SetUniformVec4("u_color", r, g, b, 1.0f);
        shader.SetUniformMat4("u_MVP", mvp);
        
        model = glm::translate(glm::mat4(1.0f), offset);
        mvp = proj * view * model;
        
        renderer.Draw(va, ib, shader);
        
        if (r > 0.95f || r < 0.05f) pong = !pong;
        if (pong) r = Lerp(r, 1.0f, i);
        else      r = Lerp(r, 0.0f, i);

        if (offset.x > (WIDTH-100.0f) || offset.x < 0+100.0f) x *= -1;
        if (offset.y > (HEIGHT-100.0f) || offset.y < 0+100.0f) y *= -1;

        offset.x += x;
        offset.y += y;
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}
