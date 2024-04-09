#pragma once
#include "Scene.h"
#include "../layer/Instancing/RendererInstanced.h"
#include <cstdlib>

class RigidBody {
public:
    glm::vec2 pos_old;
    glm::vec2* pos;
    glm::vec2 acceleration;
    float bouncines;

    void updatePosition(float dt) {
        const glm::vec2 deltaPos = *pos - pos_old;
        pos_old = *pos;
        *pos = *pos + deltaPos + acceleration*dt*dt;
        acceleration = {};
    }

    void accelerate(glm::vec2 acc) {
        acceleration += acc;
    }

    void velocity(glm::vec2 vel) {
        pos_old = *pos - vel;
    }
};

class Constraint {
public:
    glm::vec2 topLeft;
    glm::vec2 bottomRight;
    glm::vec2 centre;

    Constraint(glm::vec2 topLeft, glm::vec2 bottomRight)
        : topLeft(topLeft), bottomRight(bottomRight), centre((bottomRight.x + topLeft.x)/2, ((bottomRight.y + topLeft.y)/2))
    { }
    
    void ApplyCircle(RigidBody& rb, glm::vec2 scale) {
        glm::vec2& pos = *rb.pos;
        glm::vec2 displacement = -centre + pos;
        float displaceDist = displacement.x*displacement.x + displacement.y*displacement.y;
        float radius = HEIGHT/2;
        
        if (displaceDist > (radius - scale.x)*(radius - scale.x)) {
            pos = centre + glm::normalize(displacement) * (radius - scale.x);
        }
    }
    void ApplyRect(RigidBody& rb, glm::vec2 scale) {
        glm::vec2& pos = *rb.pos;
        glm::vec2 vel = pos - rb.pos_old;
        
        if (pos.x > bottomRight.x - scale.x) { // right
            vel = pos - rb.pos_old;
            vel.x *= -1;
            pos.x = bottomRight.x - scale.x; 
            rb.velocity(vel * rb.bouncines);
        }
        else if (pos.x < topLeft.x + scale.x) { // left
            vel = pos - rb.pos_old;
            vel.x *= -1;
            pos.x = topLeft.x + scale.x;
            rb.velocity(vel * rb.bouncines);
        }
        
        if (pos.y > topLeft.y - scale.y) {      // top
            vel = pos - rb.pos_old;
            vel.y *= -1;
            pos.y = topLeft.y - scale.y;
            rb.velocity(vel * rb.bouncines);
        }
        else if (pos.y < bottomRight.y + scale.y) { // bottom
            vel = pos - rb.pos_old;
            vel.y *= -1;
            pos.y = bottomRight.y + scale.y;
            rb.velocity(vel * rb.bouncines);
        }

    }
};


namespace Scene {
class VerletInstanced : public Scene {
private:
    constexpr static int m_ObjCount = 100000;
    int m_SpawnRate = m_ObjCount;
    Pos_Scale_Col* m_ObjData = new Pos_Scale_Col[m_ObjCount];
    RigidBody* m_Bodies = new RigidBody[m_ObjCount];
    Constraint m_Constraint;
    glm::vec2 m_Gravity;
    RendererInstanced<QuadData, Pos_Scale_Col, m_ObjCount> m_Renderer;
public:
    VerletInstanced() 
        : m_Constraint({0, HEIGHT}, {WIDTH, 0}), m_Gravity({0, -1000}), m_Renderer(m_ObjData) 
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
            // float diffx = WIDTH/m_ObjCount;
            // m_ObjData[i].position = glm::vec2(WIDTH * p - diffx/2, HEIGHT-20);
            m_ObjData[i].position = glm::vec2(WIDTH - 10, HEIGHT/2);
            m_ObjData[i].scale = glm::vec2(5);
            m_ObjData[i].color = glm::vec4(1,1,1,1);
            m_Bodies[i].pos = &m_ObjData[i].position;
            m_Bodies[i].pos_old = m_ObjData[i].position;
            m_Bodies[i].bouncines = 1.0f - p;
            m_Bodies[i].velocity(glm::vec2(-5, 10));
        }
        m_ObjData[0].color = glm::vec4(0,0.5,1,1);
        m_ObjData[m_ObjCount-1].color = glm::vec4(1,0.5,0,1);
        m_SpawnRate = m_ObjCount;
    }

    void Update(float dt) override {
        static int enabledCount = m_ObjCount; 
        static float spawnTimer = 0;
        spawnTimer += dt;
        if (spawnTimer >= 1.0f/m_SpawnRate && enabledCount < m_ObjCount) {
            spawnTimer = 0;
            enabledCount++;
        }
        for (int i = 0; i < enabledCount; i++) {
            RigidBody& body = m_Bodies[i];
            body.accelerate(m_Gravity);
            m_Constraint.ApplyCircle(body, m_ObjData->scale);
            body.updatePosition(dt);
        }
    }

    void Render() override {
        Render::Clear(0, 0, 0, 1);
        m_Renderer.Draw();
    }
};
}

