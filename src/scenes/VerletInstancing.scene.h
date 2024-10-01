#pragma once
#include "Scene.h"
#include "../layer/Instancing/RendererInstanced.h"
#include "../layer/Input.h"
#include <GLFW/glfw3.h>
#define PI glm::pi<float>()
#define TwoPI 2 * glm::pi<float>()

class RigidBody {
public:
    glm::vec2 pos_old;
    glm::vec2* pos;
    glm::vec2 acceleration;
    float bouncines;
    float boundBouncines;
    bool iskinematic;
    bool isBound;

    void updatePosition(float dt) {
        if (iskinematic) 
            return;
        const glm::vec2 deltaPos = *pos - pos_old;
        pos_old = *pos;
        *pos = *pos + deltaPos + acceleration*dt*dt;
        acceleration = {};
    }

    void accelerate(glm::vec2 acc) {
        if (iskinematic) 
            return;
        acceleration += acc;
    }

    void velocity(glm::vec2 vel) {
        if (iskinematic) 
            return;
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
        if (!rb.isBound)
            return;
        glm::vec2 displace = -centre + *rb.pos;
        float theta = atan(displace.y/displace.x);
        float sqrtDist = (displace.x * displace.x) + (displace.y * displace.y);
        float radius = HEIGHT/2 - scale.x;
        if (displace.x < 0) radius *= -1;
        glm::vec2 vel = *rb.pos - rb.pos_old;

        if (sqrtDist > radius*radius) {
            *rb.pos = centre + radius * glm::vec2(glm::cos(theta), glm::sin(theta));
            // rb.pos_old = glm::vec2(0);
            displace = glm::normalize(displace);
            vel -= (rb.boundBouncines + 1) * displace * glm::dot(vel, displace);
            rb.velocity(vel);
        }
    }
    void ApplyRect(RigidBody& rb, glm::vec2 scale) {
        if (!rb.isBound)
            return;
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

struct SimData
{
    int EnabledCount = 1;
    double SpawnFreq = 999999999999999;
    double SpawnTimer = 0;
    float SpawnAngle = PI/2;
    float SpawnAngleDisplacement = -PI/4;
    float SpawnAngleFreq = TwoPI;
    float SpawnRadiusFreq = 1/100.0f * TwoPI;
    float SpawnColorFreq = 1/100.0f * TwoPI;
    float maxSpeed = 10;
    int subSteps = 5;
    float subDt = 0;
    glm::vec2 Gravity = {0, -1000};
};

struct Boundry
{
    glm::vec2 centre;
    glm::vec2 scale;

    bool contains(glm::vec2 point) {
        return (
            point.x <= centre.x + scale.x/2 && 
            point.x >= centre.x - scale.x/2 && 
            point.y <= centre.y + scale.y/2 && 
            point.y >= centre.y - scale.y/2
        );
    }
};

template<int Capacity>
class QuadTree {
public:
    bool isDivided;
public:
    QuadTree(glm::vec2 centre, glm::vec2 scale) : 
        isDivided(false), m_Boundry({centre, scale}), m_ObjectCount(0) {
        for (int i=0; i < 4; i++)
            m_Cells[i] = nullptr;
    }
    ~QuadTree() {
        Delete(this);
    }

    bool Insert(glm::vec2 pos, int objID) {
        if (!m_Boundry.contains(pos))
            return false;
        if (m_ObjectCount < Capacity) {
            m_ObjectCount++;
            m_Objects[m_ObjectCount-1] = objID;
            return true;
        }
        if (!isDivided) {
            SubDivide();
        }
        for (int i=0; i < 4; i++) {
            if (m_Cells[i]->Insert(pos, objID)) {
                return true;
            }
        }
        return false;
    }

private:
    Boundry m_Boundry;
    unsigned int m_ObjectCount;
    union {
        int m_Objects[4];
        QuadTree<Capacity>* m_Cells[4];
    };

    void SubDivide() {
        glm::vec2& C = m_Boundry.centre;
        glm::vec2& S = m_Boundry.scale;
        m_Cells[0] = new QuadTree<Capacity>(glm::vec2(C + S/4.0f), S/2.0f);
        m_Cells[1] = new QuadTree<Capacity>(glm::vec2(C.x - S.x/4.0f, C.y + S.y/4.0f), S/2.0f);
        m_Cells[2] = new QuadTree<Capacity>(glm::vec2(C.x + S.x/4.0f, C.y - S.y/4.0f), S/2.0f);
        m_Cells[3] = new QuadTree<Capacity>(glm::vec2(C - S/4.0f), S/2.0f);
        isDivided = true;
    }

    void Delete(QuadTree<Capacity>* tree) {
        if (!tree->isDivided) // if one child cell is null, all child cells are null 
            return;
        for (int i=0; i < 4; i++) {
            Delete(m_Cells[i]); // delete all children's child cells
            delete m_Cells[i];  // delete chilren
        }
    }
};


namespace Scene {
class VerletInstanced : public Scene {
private:
    constexpr static int m_ObjCount = 5;
    Pos_Scale_Col* m_ObjData = new Pos_Scale_Col[m_ObjCount+2];
    RigidBody* m_Bodies = new RigidBody[m_ObjCount+1];
    SimData m_SimData;
    Constraint m_Constraint;
    RendererInstanced<QuadData, Pos_Scale_Col, m_ObjCount+2> m_Renderer;
    QuadTree<4> m_QTree;
public:
    VerletInstanced() 
        : m_Constraint({0, HEIGHT}, {WIDTH, 0}), m_Renderer(m_ObjData), m_QTree({WIDTH/2, HEIGHT/2}, {WIDTH, HEIGHT}) 
    {
        m_Renderer.ShaderInit("assets/shaders/instancing/BasicColorScale.vert", 
                              "assets/shaders/instancing/CircleInRectColor.frag");
        m_Renderer.InstanceShader->SetUniform<float>("u_CullRadius", 0.5f);
        m_Renderer.InstanceShader->SetUniform<float>("u_EdgeSmooth", 1.2f);
    }
    ~VerletInstanced() {
        delete [] m_ObjData;
        delete [] m_Bodies;
    }

    void Start() override {
        m_SimData.SpawnFreq = 200;
        m_SimData.SpawnAngleDisplacement = -PI/4;
        m_SimData.SpawnAngleFreq = 1/600.0f * TwoPI;
        m_SimData.SpawnRadiusFreq = 1/200.0f * TwoPI;
        m_SimData.SpawnColorFreq = 1/50.0f;
        
        // float p = 0;
        float ip = 0;
        for (int i = 0; i < m_ObjCount; i++) {
            // p = (i+1.0f)/(m_ObjCount);
            ip = i + 1.0f;
            m_ObjData[i+2].position = glm::vec2(WIDTH/2, HEIGHT/2);
            // m_ObjData[i+2].scale = 2.0f * glm::vec2(4 + glm::sin(ip * m_SimData.SpawnRadiusFreq));
            m_ObjData[i+2].scale = glm::vec2(8.0f);
            m_ObjData[i+2].color = glm::vec4(glm::sin(ip * m_SimData.SpawnColorFreq), 0.3, 1-glm::sin(ip * m_SimData.SpawnColorFreq), 1);
            // m_ObjData[i+2].color = glm::vec4(p, 0.3, 1-p, 1);
            m_Bodies[i+1].pos = &m_ObjData[i+2].position;
            m_Bodies[i+1].pos_old = *m_Bodies[i+1].pos;
            m_Bodies[i+1].bouncines = 0.0f;
            m_Bodies[i+1].boundBouncines = 0.0f;
            m_Bodies[i+1].iskinematic = false;
            m_Bodies[i+1].isBound = true;
            float theta = m_SimData.SpawnAngleDisplacement + m_SimData.SpawnAngle/2 * (sin(ip * m_SimData.SpawnAngleFreq) - 1);
            m_Bodies[i+1].velocity(8.0f * glm::vec2(cos(theta), sin(theta)));
            m_QTree.Insert(m_ObjData[i+2].position, i+2);
        }
        // set graphic for contraint
        m_ObjData[0].position = glm::vec2(WIDTH/2, HEIGHT/2);
        m_ObjData[0].scale = glm::vec2(HEIGHT/2);
        m_ObjData[0].color = glm::vec4(0,0,0,1);

        // set graphic for god hand
        m_ObjData[1].position = glm::vec2(Input::GetMousePos().x, HEIGHT - Input::GetMousePos().y);
        m_ObjData[1].scale = glm::vec2(50.0f);
        m_ObjData[1].color = glm::vec4(0.1, 1.0, 0.0, 1); 
        m_Bodies[0].pos = &m_ObjData[1].position;
        m_Bodies[0].pos_old = *m_Bodies[0].pos;
        m_Bodies[0].bouncines = 0.0f;
        m_Bodies[0].boundBouncines = 0.0f;
        m_Bodies[0].iskinematic = true;
        m_Bodies[0].isBound = false;
        m_Bodies[0].velocity(glm::vec2(0.0f));
    }

    void Collide(RigidBody& rbA, float radiusA, RigidBody& rbB, float radiusB) {
        glm::vec2 axis = -*rbA.pos + *rbB.pos;
        float dist = glm::length(axis);

        if (dist <= radiusA + radiusB) {
            float overlap = radiusA + radiusB - dist;
            axis /= dist;
            
            if (!rbA.iskinematic) {
                *rbA.pos -= axis * overlap/2.0f;
                glm::vec2 velA = *rbA.pos - rbA.pos_old;
                velA += (rbA.bouncines) * velA;
                rbA.velocity(velA);
            }
            
            if (!rbB.iskinematic) {
                *rbB.pos += axis * overlap/2.0f;
                glm::vec2 velB = *rbB.pos - rbB.pos_old;
                velB += (rbB.bouncines) * velB;
                rbB.velocity(velB);
            }
        }
    }

    void ApplyMaxSpeed (RigidBody& rb) {
        float speedSqared = glm::length(*rb.pos - rb.pos_old);
        if (speedSqared > m_SimData.maxSpeed) {
            rb.velocity(glm::vec2((*rb.pos - rb.pos_old))/speedSqared * m_SimData.maxSpeed);
        }
    }

    void Update(float dt) override {
        m_SimData.subDt = dt / (float)m_SimData.subSteps;
        
        for (int s = 0; s < m_SimData.subSteps; s++) {
            m_SimData.SpawnTimer += m_SimData.subDt;
            if (m_SimData.SpawnTimer >= 1.0/m_SimData.SpawnFreq && m_SimData.EnabledCount < m_ObjCount) {
                m_SimData.SpawnTimer = 0;
                m_SimData.EnabledCount++;
            }
            for (int i = 0; i < m_SimData.EnabledCount+1; i++) {
                RigidBody& body = m_Bodies[i];
                body.accelerate(m_SimData.Gravity);
                body.updatePosition(m_SimData.subDt);
                for (int j = 0; j < m_SimData.EnabledCount+1; j++) { 
                    if (i == j) continue;
                    Collide(m_Bodies[i], m_ObjData[i+1].scale.x, m_Bodies[j], m_ObjData[j+1].scale.x);
                }
                m_Constraint.ApplyCircle(body, m_ObjData[i+1].scale);
            }
        }
        m_ObjData[1].position = Lerp(m_ObjData[1].position, 
                                     glm::vec2(Input::GetMousePos().x, HEIGHT - Input::GetMousePos().y), 10 * dt);
        
        if (Input::Button(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS))
            m_ObjData[1].scale = Lerp(m_ObjData[1].scale, glm::vec2(8.0f), dt * 10.0f);
        else
            m_ObjData[1].scale = Lerp(m_ObjData[1].scale, glm::vec2(50.0f), dt * 10.0f);
    }

    glm::vec2 Lerp(glm::vec2 a, glm::vec2 b, float p) {
        return a + p * (b-a);
    }

    void Render() override {
        Render::Clear(0.9, 0.9, 0.9, 1);
        m_Renderer.Draw();
    }

};
}

