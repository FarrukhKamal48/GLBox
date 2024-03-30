#pragma once

#include "Scene.h"
#include "../layer/Instancing/RendererInstanced.h"

namespace Scene {

class Instancer : public Scene {
private:
    static const int m_ObjCount = 512500;
    constexpr static const float m_MoveSpeed = 1000;
    constexpr static const float m_Bounciness = 0.9;
    RendererInstanced<QuadData, Pos2D> m_Renderer;
    Pos2D m_Tranlations[m_ObjCount];
    glm::vec2 m_Inc[m_ObjCount];
    
public:
    Instancer() : m_Renderer(m_Tranlations, m_ObjCount) { 
        m_Renderer.ShaderInit("assets/shaders/instancing/Basic.vert", 
                              "assets/shaders/instancing/CircleInRect.frag");
        m_Renderer.InstanceShader->SetUniform("u_CullRadius", 0.5f);
    }
    ~Instancer() { }

    void Start() override {
        for (int i = 0; i < m_ObjCount; i++) {
            m_Tranlations[i].position = glm::vec2(-WIDTH/2 + 5, 0);
            m_Inc[i].x = (i+1.0f)/m_ObjCount * m_MoveSpeed;
            m_Inc[i].y = (i+1.0f)/m_ObjCount * m_MoveSpeed;
        }
    }

    void Update(float dt) override {
        for (int i = 0; i < m_ObjCount; i++) {
            float& posX = m_Tranlations[i].position.x;
            if (posX > WIDTH-5) {
                // m_Inc[i].x *= -m_Bounciness;
                posX = 5;
            }
            else if (posX < 5) {
                // m_Inc[i].x *= -m_Bounciness;
                posX = WIDTH-5;
            }
            posX += m_Inc[i].x * dt;
            
            float& posY = m_Tranlations[i].position.y;
            if (posY > HEIGHT-5) {
                // m_Inc[i].y *= -m_Bounciness;
                posY = 5;
            }
            else if (posY < 5) {
                // m_Inc[i].y *= -m_Bounciness;
                posY = HEIGHT-5;
            }
            posY += m_Inc[i].y * dt;
        }
    }
    
    void Render() override {
        m_Renderer.Draw();
    }
    
};};
