#pragma once
#include "Scene.h"
#include "../layer/Instancing/RendererInstanced.h"

namespace Scene {

class Instancer : public Scene {
private:
    constexpr static int m_ObjCount = 200000;
    constexpr static float m_MoveSpeed = 1000;
    constexpr static float m_Bounciness = 0.9;
    Pos2D* m_Tranlations = new Pos2D[m_ObjCount];
    float m_Inc;
    RendererInstanced<MeshType::Quad, VertexType::Pos2D, m_ObjCount> m_Renderer;
    
public:
    Instancer() : m_Renderer(m_Tranlations) { 
        m_Renderer.ShaderInit("assets/shaders/instancing/Basic.vert", 
                              "assets/shaders/instancing/CircleInRect.frag");
        m_Renderer.InstanceShader->SetUniform("u_CullRadius", 0.5f);
    }
    ~Instancer() { }

    void Start() override {
        for (int i = 0; i < m_ObjCount; i++) {
            m_Tranlations[i].position = glm::vec2(-WIDTH/2 + 5, 0);
        }
    }

    void Update(float dt) override {
        for (int i = 0; i < m_ObjCount; i++) {
            m_Inc = (i+1.0f)/m_ObjCount * m_MoveSpeed;
            float& posX = m_Tranlations[i].position.x;
            if (posX > WIDTH-5) {
                posX = 5;
            }
            else if (posX < 5) {
                posX = WIDTH-5;
            }
            posX += m_Inc * dt;
            
            float& posY = m_Tranlations[i].position.y;
            if (posY > HEIGHT-5) {
                posY = 5;
            }
            else if (posY < 5) {
                posY = HEIGHT-5;
            }
            posY += m_Inc * dt;
        }
    }
    
    void Render() override {
        m_Renderer.Draw();
    }
    
};};
