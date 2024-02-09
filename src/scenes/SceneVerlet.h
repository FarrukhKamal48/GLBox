#pragma once
#include <memory>
#include "Scene.h"
#include "../Renderer.h"
#include "../Texture.h"
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/ext/matrix_clip_space.hpp"
#include "../primatives/PrimativeCircle.h"
#include "../primatives/PrimativeRect.h"

long long int GetStartDelay() {
    return 1;
}

namespace Scene {

struct VerletObject {
    glm::vec2 pos;
    glm::vec2 vel;
    glm::vec2 acc;
    float radius;
    float bounciness;
    Primative::Circle circle;
    VerletObject() :
        pos(glm::vec2(WIDTH/2, HEIGHT/2)), vel(glm::vec2(-10, 0)), acc(glm::vec2(0.0f, -1.0f)), 
        radius(50), bounciness(0.3) {}

    VerletObject(glm::vec2 pos, glm::vec2 vel, glm::vec2 acc, float radius, float bounciness, const Primative::Circle& circle) :
        pos(pos), vel(vel), acc(acc), radius(radius), bounciness(bounciness), circle(circle) {}
};
struct Constraint {
    glm::vec2 centre;
    float radius;
    Primative::Circle circle;

    Constraint(glm::vec2 centre, float radius) 
    : centre(centre), radius(radius), circle(centre, radius) {}
};

class Verlet : public Scene {
private:
    static const int m_OBJ_COUNT = 1000;
    VerletObject m_OBJS[m_OBJ_COUNT];
    
    int m_subSteps = 1;
    float m_eulerSplitProportion = 0.5f;
    
    Constraint m_Constraint;
    
    glm::mat4 m_Proj;
    glm::mat4 m_View;

public:
    Verlet() : 
        m_Constraint(glm::vec2(WIDTH/2, HEIGHT/2), HEIGHT/2),
        m_Proj(glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
    { }
    ~Verlet() { }

    void Start() override { 
        m_eulerSplitProportion = 0.5;

        for (int i=0; i<m_OBJ_COUNT; i++) {
            m_OBJS[i].pos = glm::vec2(WIDTH/2+(i+1)*10, HEIGHT/2+5*(i+1));
            m_OBJS[i].vel += glm::vec2((i+1)*10, 5*(i+1));
            m_OBJS[i].acc *= 2;
            m_OBJS[i].bounciness = 0.9f;
            m_OBJS[i].radius = (i+1.0f)/m_OBJ_COUNT * 5.0f;
            m_OBJS[i].circle.SetRadius(m_OBJS[i].radius);
        }
        m_Constraint.circle.SetColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void Collide(VerletObject& objA, VerletObject& objB) {
        glm::vec2 A_to_B = objB.pos - objA.pos;
        float dist = glm::length(A_to_B);
        float overlap = (objA.radius + objB.radius - dist) / 2;

        if (dist < (objA.radius + objB.radius)) {
            objA.pos += -A_to_B/dist * overlap/2.0f;
            objB.pos += A_to_B/dist * overlap/2.0f;
        }
    }
    void Solve(VerletObject& obj) {
        obj.vel += obj.acc * m_eulerSplitProportion;
        obj.pos += obj.vel;
        obj.vel += obj.acc * (1-m_eulerSplitProportion);

        glm::vec2 displacment = obj.pos - m_Constraint.centre;
        float dist = glm::length(displacment);

        if (dist >= m_Constraint.radius - obj.radius) {
            glm::vec2 normVel = glm::dot(displacment/dist, obj.vel) * displacment/dist;
            obj.pos = m_Constraint.centre + (displacment/dist * (m_Constraint.radius - obj.radius));
            obj.vel -= (1.0f+obj.bounciness) * normVel;
        }
    }
    
    void Update (float deltaTime) override {
        // return;
        for (int i=0; i<m_OBJ_COUNT; i++) {
            Solve(m_OBJS[i]);
        }
    }
    
    void Render() override {
        Renderer renderer;
        renderer.Clear(1, 1, 1, 1);

        m_Constraint.circle.Draw(m_Proj, m_View);
        
        for (int i=0; i<m_OBJ_COUNT; i++) {
            m_OBJS[i].circle.SetCentre(m_OBJS[i].pos);

            float p = (float)i/(m_OBJ_COUNT-1);
            m_OBJS[i].circle.SetColor(p, m_OBJ_COUNT-i+1, 1-p, 1.0f);

            m_OBJS[i].circle.Draw(m_Proj, m_View);
        }
    }
};
};

