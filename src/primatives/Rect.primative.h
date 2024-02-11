#pragma once
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

class Rect {
public:
    Vertex verticies[4];
    VertexBufferLayout layout;
private:
    glm::vec2 m_Centre;
    glm::vec2 m_Scale;
    
public:
    Rect() :
        m_Centre(glm::vec2(WIDTH/2, HEIGHT/2)),
        m_Scale(glm::vec2(50, 50))
    { 
        verticies[0].Position = glm::vec2(-1, -1) * m_Scale + m_Centre;
        verticies[0].UV = { 0.0f, 0.0f };
        verticies[0].Color = { 1.0f, 0.0f, 0.0f, 1.0f };
        
        verticies[1].Position = glm::vec2(1, -1) * m_Scale + m_Centre;
        verticies[1].UV = { 1.0f, 0.0f };
        verticies[1].Color = { 1.0f, 0.0f, 0.0f, 1.0f };
        
        verticies[2].Position = glm::vec2(1, 1) * m_Scale + m_Centre;
        verticies[2].UV = { 1.0f, 1.0f };
        verticies[2].Color = { 1.0f, 0.0f, 0.0f, 1.0f };
        
        verticies[3].Position = glm::vec2(-1, 1) * m_Scale + m_Centre;
        verticies[3].UV = { 0.0f, 1.0f };
        verticies[3].Color = { 1.0f, 0.0f, 0.0f, 1.0f };
        
        layout.Push<float>(2);
        layout.Push<float>(2);
        layout.Push<float>(4);
    }

    void SetCentre(glm::vec2 centre) {
        for (Vertex& v : verticies) {
            v.Position -= m_Centre;
            v.Position += centre;
        }
        m_Centre = centre;
    }
    
    void SetScale(glm::vec2 scale) {
        for (Vertex& v : verticies) {
            v.Position -= m_Centre;
            v.Position /= m_Scale;

            v.Position *= scale;
            v.Position += m_Centre;
        }
        m_Scale = scale;
    }
    
    void SetColor(float r, float g, float b, float a) {
        verticies[0].Color = {r, g, b, a};
        verticies[1].Color = {r, g, b, a};
        verticies[2].Color = {r, g, b, a};
        verticies[3].Color = {r, g, b, a};
    }
   
};

}
