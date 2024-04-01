#pragma once
#include "Scene.h"
#include "../layer/Instancing/RendererInstanced.h"

namespace Scene {

class Instancer : public Scene {
private:
    constexpr static int m_ObjCount = 200000;
    constexpr static float m_MoveSpeed = 1000;
    constexpr static float m_Bounciness = 0.9;
    Pos2D_RGBA* m_Tranlations = new Pos2D_RGBA[m_ObjCount];
    float m_Inc;
    RendererInstanced<MeshType::Quad, VertexType::Pos2D_RGBA, m_ObjCount> m_Renderer;
    
public:
    Instancer() : m_Renderer(m_Tranlations) { 
        m_Renderer.ShaderInit("assets/shaders/instancing/BasicColor.vert", 
                              "assets/shaders/instancing/CircleInRectColor.frag");
        m_Renderer.InstanceShader->SetUniform("u_CullRadius", 0.5f);
    }
    ~Instancer() { }

    void Start() override {
        static float p = 0;
        for (int i = 0; i < m_ObjCount; i++) {
            m_Tranlations[i].position = glm::vec2(-WIDTH/2 + 5, 0);
            p = (i+1.0f)/m_ObjCount;
            m_Tranlations[i].color = glm::vec4(1-p, 0.5, p, 1);
        }
    }

    void Update(float dt) override {
        for (int i = 0; i < m_ObjCount; i++) {
            m_Inc = (i+1.0f)/m_ObjCount * m_MoveSpeed * dt;
            
            float& posX = m_Tranlations[i].position.x;
            float& posY = m_Tranlations[i].position.y;
            
            if (posX > WIDTH-5)
                posX = 0;
            else if (posX < 5)
                posX = WIDTH;
            
            if (posY > HEIGHT-5)
                posY = 0;
            else if (posY < 5)
                posY = HEIGHT;
            
            posX += m_Inc;
            posY += m_Inc;
        }
    }
    
    void Render() override {
        m_Renderer.Draw();
    }
    
};};
