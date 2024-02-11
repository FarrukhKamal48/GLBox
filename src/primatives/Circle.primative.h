#pragma once
#include <array>
#include <cstring>
#include <iostream>
#include <memory>
#include "../layer/Renderer.h"
#include "../layer/Texture.h"
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/ext/matrix_clip_space.hpp"

struct Vertex {
    glm::vec2 Position;
    glm::vec2 UV;
    glm::vec4 Color;
};

namespace Primative {

class Circle {
public:
    std::unique_ptr<Shader> shader;

    std::array<Vertex, 4> vertexData;
private:
    std::unique_ptr<VertexBuffer> m_VertexBuffer;

    glm::vec2 m_Centre;
    float m_Radius;
    glm::mat4 m_Model;
    
public:
    Circle() :
        m_Centre(glm::vec2(WIDTH/2, HEIGHT/2)),
        m_Radius(50.0f),
        m_Model(glm::translate(glm::mat4(1.0f), glm::vec3(m_Centre, 0.0f)))
    { 
        Init(); 
    }
    
    Circle(glm::vec2 centre, float radius) :
        m_Centre(centre),
        m_Radius(radius),
        m_Model(glm::translate(glm::mat4(1.0f), glm::vec3(centre, 0.0f)))
    { 
        Init(); 
    }
    
    Circle(const Circle& other) :
        m_Centre(other.m_Centre),
        m_Radius(other.m_Radius),
        m_Model(other.m_Model)
    { 
        Init(); 
    }
    ~Circle() { }

    void SetRadius(float radius) {
        m_Model[0][0] *= radius/m_Radius;
        m_Model[1][1] *= radius/m_Radius;
        m_Radius = radius;
        shader->Bind();
        shader->SetUniform("u_EdgeSmooth", 1.2f/m_Radius);
    }

    void SetCentre(glm::vec2 position) {
        m_Model[3][0] = position.x;
        m_Model[3][1] = position.y;
        m_Centre = position;
    }
    
    void SetColor(float r, float g, float b, float a) {
        shader->Bind();
        shader->SetUniformVec4("u_Color", r, g, b, a);
    }

    // void Draw(glm::mat4& Proj, glm::mat4 View) {
    //     shader->Bind();
    //     shader->SetUniformMat4("u_MVP", Proj * View * m_Model);
    //     
    //     Renderer renderer;
    //     renderer.Draw(*vertexArray, *indexBuffer, *shader);
    // }
    
private:
    void Init() {
        vertexData[0].Position = { -m_Radius, -m_Radius };
        vertexData[0].UV = { 0.0f, 0.0f };
        vertexData[0].Color = { 1.0f, 0.0f, 0.0f, 1.0f };
        
        vertexData[1].Position = { m_Radius, -m_Radius };
        vertexData[1].UV = { 1.0f, 0.0f };
        vertexData[1].Color = { 1.0f, 0.0f, 0.0f, 1.0f };
        
        vertexData[2].Position = { m_Radius,  m_Radius };
        vertexData[2].UV = { 1.0f, 1.0f };
        vertexData[2].Color = { 1.0f, 0.0f, 0.0f, 1.0f };

        vertexData[3].Position = { -m_Radius,  m_Radius };
        vertexData[3].UV = { 0.0f, 1.0f };
        vertexData[3].Color = { 1.0f, 0.0f, 0.0f, 1.0f };
    }
   
};

}
