#pragma once
#include "../layer/Renderer.h"
#include "Vertex.h"

namespace Mesh {

class Quad {
public:
    static const int VertexCount = 4;
private:
    Vertex::PosUvCol m_Verticies[VertexCount];
    glm::vec2 m_Centre;
    glm::vec2 m_Scale;
    
public:
    Quad() :
        m_Centre(glm::vec2(WIDTH/2, HEIGHT/2)),
        m_Scale(glm::vec2(50, 50))
    { 
        m_Verticies[0].Position = glm::vec2(-1, -1) * m_Scale + m_Centre;
        m_Verticies[0].UV = { 0.0f, 0.0f };
        m_Verticies[0].Color = { 1.0f, 0.0f, 0.0f, 1.0f };
        
        m_Verticies[1].Position = glm::vec2(1, -1) * m_Scale + m_Centre;
        m_Verticies[1].UV = { 1.0f, 0.0f };
        m_Verticies[1].Color = { 1.0f, 0.0f, 0.0f, 1.0f };
        
        m_Verticies[2].Position = glm::vec2(1, 1) * m_Scale + m_Centre;
        m_Verticies[2].UV = { 1.0f, 1.0f };
        m_Verticies[2].Color = { 1.0f, 0.0f, 0.0f, 1.0f };
        
        m_Verticies[3].Position = glm::vec2(-1, 1) * m_Scale + m_Centre;
        m_Verticies[3].UV = { 0.0f, 1.0f };
        m_Verticies[3].Color = { 1.0f, 0.0f, 0.0f, 1.0f };
    }

    inline const Vertex::PosUvCol* GetVerticies() const { return m_Verticies; }
    inline const int GetSizeOfVerticies() const { return sizeof(m_Verticies); }
    
    inline const glm::vec2 GetCentre() const { return m_Centre; }
    inline const glm::vec2 GetScale() const { return m_Scale; }
    inline const glm::vec4 GetColor() const { return m_Verticies[0].Color; }

    void SetCentre(glm::vec2 centre) {
        for (Vertex::PosUvCol& v : m_Verticies) {
            v.Position -= m_Centre; // remove old translation
            v.Position += centre;   // apply new tranlation
        }
        m_Centre = centre;          // store translation
    }
    
    void SetScale(glm::vec2 scale) {
        for (Vertex::PosUvCol& v : m_Verticies) {
            v.Position -= m_Centre;     // remove old translation
            v.Position /= m_Scale;      // & scale

            v.Position *= scale;        // apply new scale
            v.Position += m_Centre;     // & add back old translation
        }
        m_Scale = scale;                // store scale
    }
    
    void SetColor(float r, float g, float b, float a) {
        glm::vec4 color = {r, g, b, a};
        m_Verticies[0].Color = color;
        m_Verticies[1].Color = color;
        m_Verticies[2].Color = color;
        m_Verticies[3].Color = color;
    }
   
};

}
