#pragma once
#include "../layer/Renderer.h"
#include "Vertex.h"

namespace Mesh {

class Quad {
public:
    static const int VertCount = 4;
private:
    Vertex::PosUvCol m_Verticies[VertCount];
    glm::vec2 m_Centre;
    glm::vec2 m_Scale;
    
public:
    Quad();
    Quad(glm::vec2 centre, glm::vec2 scale);
    ~Quad();

    inline const Vertex::PosUvCol* GetVerticies() const { return m_Verticies; }
    inline const int GetSizeOfVerticies() const { return sizeof(m_Verticies); }
    
    inline const glm::vec2 GetCentre() const { return m_Centre; }
    inline const glm::vec2 GetScale() const { return m_Scale; }
    inline const glm::vec4 GetColor() const { return m_Verticies[0].Color; }

    void SetCentre(glm::vec2 centre);
    void SetScale(glm::vec2 scale);
    void SetColor(float r, float g, float b, float a);
};

}
