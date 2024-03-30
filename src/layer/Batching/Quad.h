#pragma once
#include "Vertex.h"
#include "Mesh.h"
#include "../Renderer.h"

namespace Batching {

class Quad {
public:
    static const int VertexCount = 4;
private:
    Batching::PosUvCol m_Verticies[VertexCount];
    glm::vec2 m_Centre;
    glm::vec2 m_Scale;
    
public:
    Quad();
    Quad(glm::vec2 centre, glm::vec2 scale);
    ~Quad();

    const float* GetVerticies() const { return (float*)m_Verticies; }
    static const int GetSizeOfVerticies() { return sizeof(m_Verticies); }
    
    inline const glm::vec2 GetCentre() const { return m_Centre; }
    inline const glm::vec2 GetScale() const { return m_Scale; }
    inline const glm::vec4 GetColor() const { return m_Verticies[0].Color; }

    void SetCentre(glm::vec2 centre);
    void SetScale(glm::vec2 scale);
    void SetColor(float r, float g, float b, float a);
};

}
