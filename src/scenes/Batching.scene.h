#pragma once
#include <memory>
#include "GL/glew.h"

#include "Scene.h"
#include "../layer/Renderer.h"
#include "../primatives/Rect.primative.h"
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/ext/matrix_clip_space.hpp"

namespace Scene {

class Batching : public Scene {
private:
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<Shader> m_Shader;

    Primative::Rect m_Shape;
    
public:
    Batching() {
        unsigned int indices[] = {
            0, 1, 2, 
            0, 2, 3
        };
        
        Renderer renderer;
        renderer.BasicBlend();

        m_VertexArray =  std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, sizeof(m_Shape.verticies));
        m_IndexBuffer =  std::make_unique<IndexBuffer>(indices, 6);
        
        m_VertexArray->AddBuffer(*m_VertexBuffer, m_Shape.layout);

        glm::mat4 proj = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 mvp = proj * view;
        
        m_Shader = std::make_unique<Shader>();
        m_Shader->Push(GL_VERTEX_SHADER, "assets/shaders/Batching.vert");
        m_Shader->Push(GL_FRAGMENT_SHADER, "assets/shaders/Batching.frag");
        m_Shader->Compile();
        m_Shader->Bind();
        m_Shader->SetUniformMat4("u_MVP", mvp);

    }
    ~Batching() { }
    
    void Render() override {
        Renderer renderer;
        renderer.Clear(1, 1, 1, 1);
        
        m_Shape.SetColor(1, 0, 0, 1);
        m_Shape.SetCentre(glm::vec2(WIDTH/2, HEIGHT/2));
        m_Shape.SetScale(glm::vec2(100, 100));
        m_VertexBuffer->SetData(m_Shape.verticies, sizeof(m_Shape.verticies));
        
        renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }
    
};

};

