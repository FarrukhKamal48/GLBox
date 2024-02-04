#pragma once
#include <memory>
#include "GL/glew.h"
#include "Scene.h"
#include "../Renderer.h"
#include "../Texture.h"
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/ext/matrix_clip_space.hpp"


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
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<Shader> m_Shader;
    
    VerletObject m_CircleObject;
    Constraint m_Constraint;
    
    glm::mat4 m_Proj;
    glm::mat4 m_View;
    glm::mat4 m_Model;
    glm::mat4 m_MVP;
    
    float m_eulerSplitProportion = 0.5f;
    
public:
    Verlet() :
        m_CircleObject(glm::vec2(WIDTH/2, HEIGHT/2), glm::vec2(0.0f), glm::vec2(0.0f, -1.0f), 50, 0.3),
        m_Constraint(glm::vec2(WIDTH/2, HEIGHT/2), HEIGHT/2),
        m_Proj(glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))),
        m_Model(glm::translate(glm::mat4(1.0f), glm::vec3(m_CircleObject.pos, 0.0f))),
        m_MVP(m_Proj * m_View * m_Model)
    { 
        float positions[] = {
            -m_CircleObject.radius, -m_CircleObject.radius, 0.0f, 0.0f,
             m_CircleObject.radius, -m_CircleObject.radius, 1.0f, 0.0f,
             0.0f                 ,  m_CircleObject.radius, 0.5f, 1.0f,
        };
        unsigned int indices[] = {
            0, 1, 2, 
        };
        
        Renderer renderer;
        renderer.BasicBlend();

        m_VertexArray = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 3 * 4 * sizeof(float));
        m_IndexBuffer =  std::make_unique<IndexBuffer>(indices, 3);
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_VertexArray->AddBuffer(*m_VertexBuffer, layout);
        
        m_Shader = std::make_unique<Shader>();
        m_Shader->Push(GL_VERTEX_SHADER, "assets/shaders/Basic.vert");
        m_Shader->Push(GL_FRAGMENT_SHADER, "assets/shaders/CircleSolid.frag");
        m_Shader->Compile();
        m_Shader->Bind();
        m_Shader->SetUniformVec4("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        m_Shader->SetUniformMat4("u_MVP", m_MVP);
    }
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

        m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_CircleObject.pos, 0.0f));
        m_MVP = m_Proj * m_View * m_Model;
        m_Shader->SetUniformMat4("u_MVP", m_MVP);
        
        float heightPercent = m_CircleObject.pos.y/HEIGHT;
        float widthPercent = abs(m_Constraint.centre.x - m_CircleObject.pos.x) / (m_Constraint.radius - m_CircleObject.radius);
        m_Shader->SetUniformVec4("u_Color", heightPercent, widthPercent, 1.0f - heightPercent, 1.0f);
        
        renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }
    
};

};

