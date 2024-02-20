#pragma once
#include "../layer/BatchRenderer.h"
#include "../meshes/Quad.h"
#include "Scene.h"

class VerletObject {
public:
    glm::vec2 pos_old;
    glm::vec2 pos;
    glm::vec2 acceleration;
    Mesh::Quad* Mesh;
    float Radius;

    void SetRadius(float radius) { 
        Mesh->SetScale(glm::vec2(radius)); 
        Radius = radius;
    }
    float GetRadius() const { return Radius; }

    void updatePosition(float dt) {
        const glm::vec2 deltaPos = pos - pos_old;
        pos_old = pos;
        pos = pos + deltaPos + acceleration*dt*dt;
        acceleration = {};
        Mesh->SetCentre(pos);
    }

    void accelerate(glm::vec2 acc) {
        acceleration += acc;
    }
};

struct CircleConstraint {
    glm::vec2 centre;
    float radius;
    CircleConstraint() : centre({WIDTH/2, HEIGHT/2}), radius(HEIGHT/2) {}
};

namespace Scene {
class Verlet : public Scene {
private:
    const unsigned int m_ObjCount = 32;
    VerletObject* m_Objs = new VerletObject[m_ObjCount];
    Mesh::Quad* m_Shapes = new Mesh::Quad[m_ObjCount];
    
    BatchRenderer<Mesh::Quad, 256> m_BatchRenderer;

    glm::vec2 gravity = {0, -2000};
    CircleConstraint m_Constraint;
    
public:
    Verlet() : 
        m_BatchRenderer(m_Shapes, m_ObjCount, glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f), 
                        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
    {
        m_BatchRenderer.ShaderInit("assets/shaders/Batching.vert", 
                                   "assets/shaders/BatchingCircle.frag");
        m_BatchRenderer.BatchShader->SetUniform("u_EdgeSmooth", 1.2f/m_Shapes[0].GetScale().x);
        m_BatchRenderer.BatchShader->SetUniform("u_CullRadius", 0.5f);
    }
    ~Verlet() { 
        delete [] m_Objs;
        delete [] m_Shapes;
    }

    void Start() override {
        for (unsigned int i=0; i<m_ObjCount; i++) {
            m_Objs[i].Mesh = &m_Shapes[i];
            // m_Objs[i].SetRadius((i+1)*5 + 10);
            m_Objs[i].SetRadius(30);
            m_Objs[i].Mesh->SetColor((float)i/m_ObjCount, 1-(float)i/m_ObjCount, 1, 1);
            m_Objs[i].Mesh->SetCentre(m_Objs[i].pos);
                
            m_Objs[i].pos = m_Constraint.centre + glm::vec2(i*20 + 100);
            m_Objs[i].pos_old = m_Objs[i].pos;
            m_Objs[i].updatePosition(0.01);
        }
    }

    void ConstrainObj(VerletObject& obj) {
        glm::vec2 displacement = -m_Constraint.centre + obj.pos;
        float displaceDist = glm::length(displacement);
        
        if (displaceDist > m_Constraint.radius - obj.GetRadius()) {
            obj.pos = m_Constraint.centre + displacement/displaceDist * (m_Constraint.radius - obj.GetRadius());
        }
    }

    void Collide(VerletObject& objA, VerletObject& objB) {
        glm::vec2 axis = -objA.pos + objB.pos;
        float dist = glm::length(axis);

        if (dist <= objA.Radius + objB.Radius) {
            float overlap = objA.Radius + objB.Radius - dist;
            objA.pos -= axis/dist * overlap/2.0f;
            objB.pos += axis/dist * overlap/2.0f;
        }
    }

    void Update(float dt) override {
        for (unsigned int i=0; i<m_ObjCount; i++) {
            m_Objs[i].accelerate(gravity);
            m_Objs[i].updatePosition(dt);
            ConstrainObj(m_Objs[i]);
            // continue;
            for (unsigned int j=0; j<m_ObjCount; j++) { 
                if (i == j) continue;
                Collide(m_Objs[i], m_Objs[j]);
            }
        }
    }
    
    void Render() override {
        Renderer::BasicBlend();
        Renderer::Clear(1, 1, 1, 1);

        m_BatchRenderer.DrawBatches();
    }
    
};}

