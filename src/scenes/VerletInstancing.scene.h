#pragma once
#include "Scene.h"
#include "../layer/Instancing/RendererInstanced.h"
#include <cstdlib>

class Constraint {
public:
    glm::vec2 topLeft;
    glm::vec2 bottomRight;
    glm::vec2 centre;

    Constraint(glm::vec2 topLeft, glm::vec2 bottomRight)
        : topLeft(topLeft), bottomRight(bottomRight), centre((bottomRight.x + topLeft.x)/2, ((bottomRight.y + topLeft.y)/2))
    { }
    
    // void Apply(glm::vec2& pos, glm::vec2 scale) {
    //     glm::vec2 displacement = -centre + pos;
    //     float displaceDist = glm::length(displacement);
    //     
    //     if (displacement.x > bottomRight.x || displacement.x < topLeft.x || displacement.y > topLeft.y || displacement.y < bottomRight.y) {
    //         pos = centre + displacement/displaceDist * (m_Constraint.radius - obj.GetRadius());
    //     }
    // }
    void Apply(glm::vec2& pos, glm::vec2 scale) {
        if (pos.x > bottomRight.x - scale.x) pos.x = bottomRight.x - scale.x;
        else if (pos.x < topLeft.x + scale.x) pos.x = topLeft.x + scale.x;
        
        if (pos.y > topLeft.y - scale.y) pos.y = topLeft.y - scale.y;
        else if (pos.y < bottomRight.y + scale.y) pos.y = bottomRight.y + scale.y;
    }
};

class RigidBody {
public:
    glm::vec2 pos_old;
    glm::vec2* pos;
    glm::vec2 acceleration;
    
    void updatePosition(float dt) {
        const glm::vec2 deltaPos = *pos - pos_old;
        pos_old = *pos;
        *pos = *pos + deltaPos + acceleration*dt*dt;
        acceleration = {};
    }

    void accelerate(glm::vec2 acc) {
        acceleration += acc;
    }
};

namespace Scene {
class VerletInstanced : public Scene {
private:
    constexpr static int m_ObjCount = 10;
    Pos_Scale_Col* m_ObjData = new Pos_Scale_Col[m_ObjCount];
    RigidBody* m_Bodies = new RigidBody[m_ObjCount];
    Constraint m_Constraint;
    glm::vec2 m_Gravity;
    RendererInstanced<QuadData, Pos_Scale_Col, m_ObjCount> m_Renderer;
public:
    VerletInstanced() 
        : m_Constraint({0, HEIGHT}, {WIDTH, 0}), m_Gravity({0, -50}), m_Renderer(m_ObjData) 
    {
        m_Renderer.ShaderInit("assets/shaders/instancing/BasicColorScale.vert", 
                              "assets/shaders/instancing/CircleInRectColor.frag");
        m_Renderer.InstanceShader->SetUniform<float>("u_CullRadius", 0.5f);
        m_Renderer.InstanceShader->SetUniform<float>("u_EdgeSmooth", 1.2f);
    }
    ~VerletInstanced() {
        delete [] m_ObjData;
    }

    void Start() override {
        static float p = 0;
        for (int i = 0; i < m_ObjCount; i++) {
            p = (i+1.0f)/m_ObjCount;
            float diffx = WIDTH/m_ObjCount;
            m_ObjData[i].position = glm::vec2(WIDTH * p - diffx/2, HEIGHT/2);
            m_ObjData[i].scale = glm::vec2(20);
            m_ObjData[i].color = glm::vec4(1,1,1,1);
            m_Bodies[i].pos = &m_ObjData[i].position;
            m_Bodies[i].pos_old = m_ObjData[i].position;
        }
    }

    void Update(float dt) override {
        for (int i = 0; i < m_ObjCount; i++) {
            RigidBody& body = m_Bodies[i];
            body.accelerate(m_Gravity);
            m_Constraint.Apply(*body.pos, m_ObjData->scale);
            body.updatePosition(dt);
        }
    }

    void Render() override {
        Render::Clear(0, 0, 0, 1);
        m_Renderer.Draw();
    }
};
}

