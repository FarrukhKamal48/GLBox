#pragma once
#include "Scene.h"
#include "../layer/Instancing/RendererInstanced.h"

namespace Scene {

class Instancer : public Scene {
private:
    constexpr static int m_ObjCount = 200000;
    constexpr static float m_MoveSpeed = 1000;
    constexpr static float m_Bounciness = 0.9;
    Vec2_Vec2_Vec4* m_ObjData = new Vec2_Vec2_Vec4[m_ObjCount];
    float m_Inc;
    RendererInstanced<QuadData, Vec2_Vec2_Vec4, m_ObjCount> m_Renderer;
    
public:
    Instancer() : m_Renderer(m_ObjData) { 
        m_Renderer.ShaderInit("assets/shaders/instancing/BasicColorScale.vert", 
                              "assets/shaders/instancing/CircleInRectColor.frag");
        m_Renderer.InstanceShader->SetUniform("u_CullRadius", 0.5f);
    }
    ~Instancer() { }

    void Start() override {
        static float p = 0;
        for (int i = 0; i < m_ObjCount; i++) {
            m_ObjData[i].position = glm::vec2(-WIDTH/2 + 5, 0);
            m_ObjData[i].scale = glm::vec2(5);
            p = (i+1.0f)/m_ObjCount;
            m_ObjData[i].color = glm::vec4(1-p, 0.5, p, 1);
        }
    }

    void Update(float dt) override {
        for (int i = 0; i < m_ObjCount; i++) {
            m_Inc = (i+1.0f)/m_ObjCount * m_MoveSpeed * dt;
            
            float& posX = m_ObjData[i].position.x;
            float& posY = m_ObjData[i].position.y;
            
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
        Render::Clear(1, 1, 1, 1);
        m_Renderer.Draw();
    }
    
};};
