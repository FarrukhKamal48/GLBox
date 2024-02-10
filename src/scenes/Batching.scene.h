#pragma once
#include <cstring>
#include <memory>
#include "GL/glew.h"

#include "Scene.h"
#include "../layer/Renderer.h"
#include "../layer/Texture.h"
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/ext/matrix_clip_space.hpp"


namespace Scene {

class Batching : public Scene {
private:
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<Shader> m_Shader;

    glm::vec2 m_Scale = glm::vec2(100);
    
public:
    Batching() {
        float centreOffset = 80;
        float verticies[] = {
            -m_Scale.x-centreOffset, -m_Scale.y, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,
             m_Scale.x-centreOffset, -m_Scale.y, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,
             m_Scale.x-centreOffset,  m_Scale.y, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f, 1.0f,
            -m_Scale.x-centreOffset,  m_Scale.y, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, 1.0f,
            
            -m_Scale.x+centreOffset, -m_Scale.y, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,
             m_Scale.x+centreOffset, -m_Scale.y, 1.0f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,
             m_Scale.x+centreOffset,  m_Scale.y, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f, 1.0f,
            -m_Scale.x+centreOffset,  m_Scale.y, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f, 1.0f,
        };
        unsigned int indices[] = {
            0, 1, 2, 0, 2, 3,
            4, 5, 6, 4, 6, 7
        };
        
        Renderer renderer;
        renderer.BasicBlend();

        m_VertexArray =  std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique< VertexBuffer>(verticies, 8 * 8 * sizeof(float));
        m_IndexBuffer =  std::make_unique<IndexBuffer>(indices, 12);
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        layout.Push<float>(4);
        m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

        glm::mat4 proj = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(WIDTH/2, HEIGHT/2, 0.0f));
        glm::mat4 mvp = proj * view * model;
        
        m_Shader = std::make_unique<Shader>();
        m_Shader->Push(GL_VERTEX_SHADER, "assets/shaders/Batching.vert");
        m_Shader->Push(GL_FRAGMENT_SHADER, "assets/shaders/Batching.frag");
        m_Shader->Compile();
        m_Shader->Bind();
        m_Shader->SetUniformVec4("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        m_Shader->SetUniformMat4("u_MVP", mvp);
    }
    ~Batching() { }
    
    void Render() override {
        Renderer renderer;
        renderer.Clear(1, 1, 1, 1);
        renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }
    
};

};

