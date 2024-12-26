#pragma once
#include <memory>
#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "Core/Layer.h"
#include "Core/Renderer.h"
#include "Core/Texture.h"


class Circle : public Layer {
private:
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Texture> m_Texutre;

    float m_CircleRadius = 100;
    
public:
    Circle() : Layer("Circle") {
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
        m_Shader->Push(GL_FRAGMENT_SHADER, "assets/shaders/CircularTexture.frag");
        m_Shader->Compile();
        m_Shader->Bind();
        m_Shader->SetUniformVec4("u_Color", 0.0f, 0.5f, 1.0f, 1.0f);
        m_Shader->SetUniformMat4("u_MVP", mvp);

        m_Texutre = std::make_unique<Texture>("assets/textures/tes_1000x1000px.png");
        m_Texutre->Bind();
        m_Shader->SetUniform("u_Texture", m_Texutre->GetSlot());
    }
    ~Circle() { }
    
    void Render() override {
        Render::Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }
    
};
