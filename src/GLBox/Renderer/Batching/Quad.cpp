#include "GLBox/Renderer/Batching/Quad.h"
#include "GLBox/Core/Application.h"


namespace Batching {

Quad::Quad() :
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
Quad::Quad(glm::vec2 centre, glm::vec2 scale) :
    m_Centre(centre), m_Scale(scale)
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

Quad::~Quad() { }

void Quad::SetCentre(glm::vec2 centre) {
    for (PosUvCol& v : m_Verticies) {
        v.Position -= m_Centre; // remove old translation
        v.Position += centre;   // apply new tranlation
    }
    m_Centre = centre;          // store translation
}

void Quad::SetScale(glm::vec2 scale) {
    for (PosUvCol& v : m_Verticies) {
        v.Position -= m_Centre;     // remove old translation
        v.Position /= m_Scale;      // & scale

        v.Position *= scale;        // apply new scale
        v.Position += m_Centre;     // & add back old translation
    }
    m_Scale = scale;                // store scale
}

void Quad::SetColor(float r, float g, float b, float a) {
    glm::vec4 color = {r, g, b, a};
    m_Verticies[0].Color = color;
    m_Verticies[1].Color = color;
    m_Verticies[2].Color = color;
    m_Verticies[3].Color = color;
}

}
