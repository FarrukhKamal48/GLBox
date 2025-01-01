#pragma once
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "GLBox/Core/Layer.h"
#include "GLBox/Renderer/Batching/BatchRenderer.h"

class Batcher : public Layer {
private:
    static const int m_ObjCount = 100;
    Batching::Quad m_Shapes[m_ObjCount];
    Batching::BatchRenderer<Batching::Quad, 100> m_BatchRenderer;
    
public:
    Batcher() 
        : Layer("Batcher")
        , m_BatchRenderer(m_Shapes, m_ObjCount, 
                          glm::ortho(0.0f, (float)RenderCommand::GetData().WindowWidth, 0.0f, (float)RenderCommand::GetData().WindowHeight, -1.0f, 1.0f), 
                          glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
    {
        m_BatchRenderer.ShaderInit("assets/shaders/Batching.vert", 
                                   "assets/shaders/BatchingCircle.frag");
        
        m_BatchRenderer.BatchShader->SetUniform("u_EdgeSmooth", 1.2f/m_Shapes[0].GetScale().x);
        m_BatchRenderer.BatchShader->SetUniform("u_CullRadius", 0.5f);
    }
    ~Batcher() { }

    void OnAttach() override {
        for (int i=0; i<m_ObjCount; i++) {
            m_Shapes[i].SetCentre(m_Shapes[i].GetCentre() + glm::vec2(sin(i), cos(i))*100.0f);
        }
    }

    void Update(float dt) override {
        for (int i=0; i<m_ObjCount; i++) {
            m_Shapes[i].SetCentre(m_Shapes[i].GetCentre() + glm::vec2(sin(i), cos(i))*50.0f*dt);
        }
    }
    
    void Render() override {
        m_BatchRenderer.DrawBatches();
    }
    
};
