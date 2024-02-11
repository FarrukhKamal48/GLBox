#pragma once
#include "../layer/Renderer.h"

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

    inline const glm::vec2 GetCentre() const { return m_Centre; }

    void SetCentre(glm::vec2 centre) {
        for (Vertex& v : verticies) {
            v.Position -= m_Centre; // remove old translation
            v.Position += centre;   // apply new tranlation
        }
        m_Centre = centre;          // store translation
    }
    
    inline const glm::vec2 GetScale() const { return m_Scale; }
    
    void SetScale(glm::vec2 scale) {
        for (Vertex& v : verticies) {
            v.Position -= m_Centre;     // remove old translation
            v.Position /= m_Scale;      // & scale

            v.Position *= scale;        // apply new scale
            v.Position += m_Centre;     // & add back old translation
        }
        m_Scale = scale;                // store scale
    }
    
    void SetColor(float r, float g, float b, float a) {
        glm::vec4 color = {r, g, b, a};
        verticies[0].Color = color;
        verticies[1].Color = color;
        verticies[2].Color = color;
        verticies[3].Color = color;
    }
   
};

}
