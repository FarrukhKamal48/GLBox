#pragma once
#include "GL/glew.h"

#include "Scene.h"
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/ext/matrix_clip_space.hpp"
#include "../layer/InstanceRenderer.h"

namespace Scene {

class Instancing : public Scene {
private:
    static const int m_ObjCount = 1024;
    constexpr static const float m_MoveSpeed = 10000;
    constexpr static const float m_Bounciness = 0.9;
    glm::vec2 m_Tranlations[m_ObjCount];
    glm::vec2 m_Inc[m_ObjCount];
    InstanceRenderer m_Renderer;
    
public:
    Instancing() : m_Renderer(m_Tranlations, m_ObjCount) { }
    ~Instancing() { }

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
            if (posX > WIDTH/2-10) {
                m_Inc[i].x *= -m_Bounciness;
                posX = WIDTH/2-10;
            }
            else if (posX < -WIDTH/2+10) {
                m_Inc[i].x *= -m_Bounciness;
                posX = -WIDTH/2+10;
            }
            posX += m_Inc[i].x * dt;
            
            float& posY = m_Tranlations[i].y;
            if (posY > HEIGHT/2-10) {
                m_Inc[i].y *= -m_Bounciness;
                posY = HEIGHT/2-10;
            }
            else if (posY < -HEIGHT/2+10) {
                m_Inc[i].y *= -m_Bounciness;
                posY = -HEIGHT/2+10;
            }
            posY += m_Inc[i].y * dt;
        }
    }
    
    void Render() override {
        m_Renderer.Draw();
    }
    
};};
