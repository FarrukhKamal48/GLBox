#pragma once
#include <cstring>
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

class Verlet : public Scene {
private:
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Texture> m_Texutre;

    float m_CircleRadius = 50;
    
public:
    Verlet() {
        float positions[] = {
            -m_CircleRadius, -m_CircleRadius, 0.0f, 0.0f,
             m_CircleRadius, -m_CircleRadius, 1.0f, 0.0f,
             m_CircleRadius,  m_CircleRadius, 1.0f, 1.0f,
            -m_CircleRadius,  m_CircleRadius, 0.0f, 1.0f,
        };
        unsigned int indices[] = {
            0, 1, 2, 
            0, 2, 3
        };
        
        Renderer renderer;
        renderer.BasicBlend();

        m_VertexArray =  std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique< VertexBuffer>(positions, 4 * 4 * sizeof(float));
        m_IndexBuffer =  std::make_unique<IndexBuffer>(indices, 6);
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

        glm::mat4 proj = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(WIDTH/2, HEIGHT/2, 0.0f));
        glm::mat4 mvp = proj * view * model;
        
        m_Shader = std::make_unique<Shader>();
        m_Shader->Push(GL_VERTEX_SHADER, "assets/shaders/Basic.vert");
        m_Shader->Push(GL_FRAGMENT_SHADER, "assets/shaders/CircleSolid.frag");
        m_Shader->Compile();
        m_Shader->Bind();
        m_Shader->SetUniformVec4("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        m_Shader->SetUniformMat4("u_MVP", mvp);
    }
    
    ~Verlet() {
        
    }
    
    void Update (float deltaTime) override {
        
    }
    
    void Render() override {
        Renderer renderer;
        renderer.Clear(0, 0, 0, 0);
        renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }
    
    void ImGuiRender() override {
        
    }
    
};

};
