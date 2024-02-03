#pragma once
#include <memory>
#include "GL/glew.h"

#include "Scene.h"
#include "../Renderer.h"
#include "../Texture.h"
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/ext/matrix_clip_space.hpp"

#define WIDTH (float)1920
#define HEIGHT (float)1080

namespace Scene {

class Triangle : public Scene {
private:
    
public:
    Triangle() {
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
    }
    
    ~Triangle() {
        
    }
    
    void Update (float deltaTime) override {
        
    }
    
    void Render() override {
    }
    
    void ImGuiRender() override {
        
    }
    
};

};
