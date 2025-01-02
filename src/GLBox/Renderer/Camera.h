#pragma once

#include "GLBox/Renderer/UnifromBuffer.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

class OrthoCamera {
public:    
    OrthoCamera(float left, float right, float bottom, float top)
        : m_Projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
        , m_Bounds({right-left, top-bottom})
        , m_CameraBuffer(&m_ProjectionView, sizeof(m_ProjectionView), s_CameraCount-1)
    { s_CameraCount++; }
    void SetProjection(float left, float right, float bottom, float top);

    const glm::vec3& GetPosition()              { return m_Position; }
    void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateMaticies(); }
    
    const float GetRotation()           { return m_ZRotation; }
    void SetRotation(float zRotation)   { m_ZRotation = zRotation; RecalculateMaticies(); }

    const glm::vec2& GetBounds()    { return m_Bounds; }

    const glm::mat4& GetProj()      { return m_Projection; };
    const glm::mat4& GetView()      { return m_View; };
    const glm::mat4& GetProjView()  { return m_ProjectionView; };
private:
    void RecalculateMaticies();
private:
    unsigned int s_CameraCount = 1;
    
    glm::mat4 m_Projection;
    glm::mat4 m_View = glm::mat4(1.0f);
    glm::mat4 m_ProjectionView = glm::mat4(1.0f);

    glm::vec3 m_Position = {0,0,0};
    float m_ZRotation = 0.0f;
    glm::vec2 m_Bounds = {0,0};

    UniformBuffer m_CameraBuffer;
};

