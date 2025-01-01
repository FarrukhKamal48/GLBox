#pragma once

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

class OrthoCamera {
public:    
    OrthoCamera(float left, float right, float bottom, float top)
        : m_Projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
    { }
    void SetProjection(float left, float right, float bottom, float top) {
        m_Projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_ProjectionView = m_Projection * m_View;
    }

    const glm::vec3& GetPosition() { return m_Position; }
    void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateMaticies(); }
    
    const float GetRotation() { return m_ZRotation; }
    void SetRotation(float zRotation) { m_ZRotation = zRotation; RecalculateMaticies(); }

    const glm::mat4& GetProj() { return m_Projection; };
    const glm::mat4& GetView() { return m_View; };
    const glm::mat4& GetProjView() { return m_ProjectionView; };
private:
    void RecalculateMaticies() {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
            glm::rotate(glm::mat4(1.0f), glm::radians(m_ZRotation), { 0, 0, 1 });
        m_View = glm::inverse(transform);
        m_ProjectionView = m_Projection * m_View;
    }
private:
    glm::mat4 m_Projection;
    glm::mat4 m_View = glm::mat4(1.0f);
    glm::mat4 m_ProjectionView = glm::mat4(1.0f);

    glm::vec3 m_Position = {0,0,0};
    float m_ZRotation = 0.0f;
};

