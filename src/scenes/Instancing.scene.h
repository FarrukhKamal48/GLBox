#pragma once
#include "GL/glew.h"

#include "Scene.h"
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/ext/matrix_clip_space.hpp"
#include "../layer/Instancing/InstanceRenderer.h"

namespace Scene {

class Instancer : public Scene {
private:
    static const int m_ObjCount = 1024;
    constexpr static const float m_MoveSpeed = 10000;
    constexpr static const float m_Bounciness = 0.9;
    glm::vec2 m_Tranlations[m_ObjCount];
    glm::vec2 m_Inc[m_ObjCount];
    Instancing::InstanceRenderer m_Renderer;
    
public:
    Instancer() : m_Renderer(m_Tranlations, sizeof(m_Tranlations), m_ObjCount) { 
        m_Renderer.ShaderInit("assets/shaders/instancing/Basic.vert", 
                              "assets/shaders/instancing/CircleInRect.frag");
        m_Renderer.InstanceShader->SetUniform("u_CullRadius", 0.5f);
    }
    ~Instancer() { }

    void Start() override {
        for (int i = 0; i < m_ObjCount; i++) {
            m_Tranlations[i] = glm::vec2(-WIDTH/2 + 10, 0);
            m_Inc[i].x = (i+1.0f)/m_ObjCount * m_MoveSpeed;
            m_Inc[i].y = (i+1.0f)/m_ObjCount * m_MoveSpeed;
        }
    }

    void Update(float dt) override {
        for (int i = 0; i < m_ObjCount; i++) {
            float& posX = m_Tranlations[i].x;
            if (posX > WIDTH-10) {
                m_Inc[i].x *= -m_Bounciness;
                posX = WIDTH-10;
            }
            else if (posX < 10) {
                m_Inc[i].x *= -m_Bounciness;
                posX = 10;
            }
            posX += m_Inc[i].x * dt;
            
            float& posY = m_Tranlations[i].y;
            if (posY > HEIGHT-10) {
                m_Inc[i].y *= -m_Bounciness;
                posY = HEIGHT-10;
            }
            else if (posY < 10) {
                m_Inc[i].y *= -m_Bounciness;
                posY = 10;
            }
            posY += m_Inc[i].y * dt;
        }
    }
    
    void Render() override {
        m_Renderer.Draw();
    }
    
};};
