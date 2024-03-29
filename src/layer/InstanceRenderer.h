#pragma once
#include "GL/glew.h"
#include <memory>

#include "../layer/Renderer.h"
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/ext/matrix_clip_space.hpp"
#include "VertexBuffer.h"

class InstanceRenderer {
private:
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<VertexBuffer> m_TransBuffer;
    std::unique_ptr<Shader> m_Shader;

    float m_Length = 10;
    glm::vec2* m_Translations;
    unsigned int m_InstaceCount;
    
public:
    InstanceRenderer(glm::vec2* translations, unsigned int instaceCount) 
        : m_Translations(translations), m_InstaceCount(instaceCount)
    {
        float positions[] = {
            -m_Length, -m_Length, 0.0f, 0.0f,
             m_Length, -m_Length, 1.0f, 0.0f,
             m_Length,  m_Length, 1.0f, 1.0f,
            -m_Length,  m_Length, 0.0f, 1.0f,
        };
        unsigned int indices[] = {
            0, 1, 2, 
            0, 2, 3
        };
        
        Renderer::BasicBlend();

        m_VertexArray =  std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
        m_TransBuffer = std::make_unique<VertexBuffer>(nullptr, m_InstaceCount * sizeof(glm::vec2), GL_DYNAMIC_DRAW);
        m_IndexBuffer =  std::make_unique<IndexBuffer>(indices, 6);
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

        VertexBufferLayout translateLayout;
        translateLayout.Push<float>(2, 1);
        m_VertexArray->AddBuffer(*m_TransBuffer, translateLayout);

        glm::mat4 proj = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(WIDTH/2, HEIGHT/2, 0.0f));
        glm::mat4 mvp = proj * view * model;
        
        m_Shader = std::make_unique<Shader>();
        m_Shader->Push(GL_VERTEX_SHADER, "assets/shaders/instancing/Basic.vert");
        m_Shader->Push(GL_FRAGMENT_SHADER, "assets/shaders/instancing/Basic.frag");
        m_Shader->Compile();
        m_Shader->Bind();
        m_Shader->SetUniformVec4("u_Color", 0.0f, 0.5f, 1.0f, 1.0f);
        m_Shader->SetUniformMat4("u_MVP", mvp);
    }
    ~InstanceRenderer() { }

    glm::vec2* GetTransforms() { return m_Translations; }

    void Draw() {
        Renderer::Clear(1, 1, 1, 1);
        
        m_TransBuffer->SetData(m_Translations, m_InstaceCount * sizeof(glm::vec2));
        
        Renderer::DrawInstanced(*m_VertexArray, *m_IndexBuffer, *m_Shader, m_InstaceCount);
    }
};
