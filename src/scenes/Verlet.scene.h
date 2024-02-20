#pragma once
#include "../layer/BatchRenderer.h"
#include "../meshes/Quad.h"
#include "Scene.h"

class VerletObject {
public:
    glm::vec2 pos_old;
    glm::vec2 pos_cur;
    glm::vec2 acceleration;
    Mesh::Quad* mesh;
    float radius;

    void SetRadius(float radius) { mesh->SetScale(glm::vec2(radius)); }
    float GetRadius(float radius) const { return radius; }

    void updatePosition(float dt) {
        const glm::vec2 deltaPos = pos_cur - pos_old;
        pos_old = pos_cur;
        pos_cur = pos_cur + deltaPos + acceleration*dt*dt;
        acceleration = {};
        mesh->SetCentre(pos_cur);
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
    const unsigned int m_ObjCount = 5;
    VerletObject* m_Objs = new VerletObject[m_ObjCount];
    Mesh::Quad* m_Shapes = new Mesh::Quad[m_ObjCount];
    
    BatchRenderer<Mesh::Quad, 8> m_BatchRenderer;

    glm::vec2 gravity = {0, -1000};
    CircleConstraint m_Constraint;
    
public:
    Verlet() : 
        m_BatchRenderer(m_Shapes, 4, glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f), 
                        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
    {
        m_BatchRenderer.ShaderInit("assets/shaders/Batching.vert", 
                                   "assets/shaders/BatchingCircle.frag");
        m_BatchRenderer.BatchShader->SetUniform("u_EdgeSmooth", 1.2f/m_Shapes[0].GetScale().x);
        m_BatchRenderer.BatchShader->SetUniform("u_CullRadius", 0.5f);
    }
    ~Verlet() { }

    void Start() override {
        for (unsigned int i=0; i<m_ObjCount; i++) {
            m_Objs[i].pos_old = {WIDTH/2 + 100*i, HEIGHT/2};
            m_Objs[i].pos_cur = m_Objs[i].pos_old;
            m_Objs[i].acceleration = {0, -5};
            
            m_Objs[i].mesh = &m_Shapes[i];
            m_Objs[i].SetRadius((i+1)*10);
            m_Objs[i].mesh->SetColor((float)i/m_ObjCount, 1-(float)i/m_ObjCount, 1, 1);
            m_Objs[i].mesh->SetCentre(m_Objs[i].pos_cur);
        }
    }

    // void ConstrainObj(VerletObject& obj) {
    //     glm::vec2 displacement = -m_Constraint.centre + obj.pos_cur;
    //     float displaceDist = glm::length(displacement);
    //     
    //     if (displaceDist > m_Constraint.radius) {
    //         
    //     }
    // }

    void Update(float dt) override {
        for (unsigned int i=0; i<m_ObjCount; i++) {
            m_Objs[i].accelerate(gravity);
            m_Objs[i].updatePosition(dt);
        }
    }
    
    void Render() override {
        Renderer::BasicBlend();
        Renderer::Clear(1, 1, 1, 1);

        m_BatchRenderer.DrawBatches();
    }
    
};}

