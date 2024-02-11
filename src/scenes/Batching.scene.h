#pragma once
#include <memory>
#include "GL/glew.h"

#include "Scene.h"
#include "../layer/Renderer.h"
#include "../layer/Batcher.h"
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

    Primative::Rect m_Shapes[3];
    Batch<3> m_Batch;
    
public:
    Batching() {

        Renderer renderer;
        renderer.BasicBlend();
        
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

    void Start() override {
        m_Shapes[0].SetCentre(glm::vec2(WIDTH/2 - 200, HEIGHT/2));
        m_Shapes[0].SetColor(1, 0, 0, 1);
        
        m_Shapes[1].SetCentre(glm::vec2(WIDTH/2 + 200, HEIGHT/2));
        m_Shapes[1].SetColor(0, 0, 1, 1);
        
        m_Shapes[2].SetCentre(glm::vec2(WIDTH/2, HEIGHT/2 - 200));
        m_Shapes[2].SetColor(0, 1, 0, 1);
    }

    void Update(float dt) override {
        
        m_Batch.SetData(m_Shapes);
    }
    
    void Render() override {
        Renderer renderer;
        renderer.BasicBlend();
        renderer.Clear(1, 1, 1, 1);
        
        // m_Shape.SetColor(1, 0, 0, 1);
        // m_Shape.SetCentre(glm::vec2(WIDTH/2, HEIGHT/2));
        // m_Shape.SetScale(glm::vec2(100, 100));
        // m_VertexBuffer->SetData(m_Shape.verticies, sizeof(m_Shape.verticies));
        
        m_Batch.Draw(*m_Shader);

        // renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }
    
};

};

