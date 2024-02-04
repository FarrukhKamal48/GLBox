#pragma once
#include <cstring>
#include <memory>
#include "GL/glew.h"

#include "Scene.h"
#include "../Renderer.h"
#include "../Texture.h"
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/ext/matrix_clip_space.hpp"
#include "../primatives/PrimativeCircle.h"


struct VerletObject {
    glm::vec2 pos;
    glm::vec2 vel;
    glm::vec2 acc;
    float radius;
    float bounciness;
    VerletObject(glm::vec2 pos, glm::vec2 vel, glm::vec2 acc) :
        pos(pos), vel(vel), acc(acc), radius(30), bounciness(0.3) {}
    VerletObject(glm::vec2 pos, glm::vec2 vel, glm::vec2 acc, float radius, float bounciness) :
        pos(pos), vel(vel), acc(acc), radius(radius), bounciness(bounciness) {}
};
struct Constraint {
    glm::vec2 centre;
    float radius;
    Constraint(glm::vec2 centre, float radius) 
    : centre(centre), radius(radius) {}
};

namespace Scene {

class Verlet : public Scene {
private:
    glm::mat4 m_Proj;
    glm::mat4 m_View;
    
    VerletObject m_CircleObject;
    Constraint m_Constraint;
    Primative::Circle2D m_Circle2D;

    float m_eulerSplitProportion = 0.5f;
    
public:
    Verlet() :
        m_Proj(glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))),
        m_CircleObject(glm::vec2(WIDTH/2, HEIGHT/2), glm::vec2(0.0f), glm::vec2(0.0f, -1.0f), 50, 0.3),
        m_Constraint(glm::vec2(WIDTH/2, HEIGHT/2), HEIGHT/2),
        m_Circle2D(m_CircleObject.pos, m_Proj, m_View)
    { }
    ~Verlet() { }

    void Start() override { 
        m_CircleObject.pos = m_Constraint.centre + glm::vec2(m_Constraint.radius - m_CircleObject.radius-200, 0);
        m_CircleObject.vel = glm::vec2(-20, 50);
        m_CircleObject.acc *= 2.0;
        m_CircleObject.bounciness = 0.3;
        m_eulerSplitProportion = 0.5;
    }
    
    void Update (float deltaTime) override {
        // return;
        
        m_CircleObject.vel += m_CircleObject.acc * m_eulerSplitProportion;
        m_CircleObject.pos += m_CircleObject.vel;
        m_CircleObject.vel += m_CircleObject.acc * (1-m_eulerSplitProportion);

        glm::vec2 displacment = m_CircleObject.pos - m_Constraint.centre;
        float dist = glm::length(displacment);

        if (dist >= m_Constraint.radius - m_CircleObject.radius) {
            glm::vec2 normVel = glm::dot(displacment/dist, m_CircleObject.vel) * displacment/dist;
            m_CircleObject.pos = m_Constraint.centre + (displacment/dist * (m_Constraint.radius - m_CircleObject.radius));
            m_CircleObject.vel -= (1.0f+m_CircleObject.bounciness) * normVel;
        }
    }
    
    void Render() override {
        Renderer renderer;
        renderer.Clear(0, 0, 0, 0);

        m_Circle2D.SetPosition(m_CircleObject.pos);
        
        float heightPercent = m_CircleObject.pos.y/HEIGHT;
        float widthPercent = abs(m_Constraint.centre.x - m_CircleObject.pos.x) / (m_Constraint.radius - m_CircleObject.radius);
        m_Circle2D.shader->SetUniformVec4("u_Color", heightPercent, widthPercent, 1.0f - heightPercent, 1.0f);
        
        renderer.Draw(*m_Circle2D.vertexArray, *m_Circle2D.indexBuffer, *m_Circle2D.shader);
    }
    
};

};

