#include "GLBox/Renderer/Camera.h"

void OrthoCamera::SetProjection(float left, float right, float bottom, float top) {
    m_Projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    m_ProjectionView = m_Projection * m_View;
    m_CameraBuffer.SetData(&m_ProjectionView, sizeof(m_ProjectionView));
    m_Bounds = {right-left, top-bottom};
}

void OrthoCamera::RecalculateMaticies() {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
        glm::rotate(glm::mat4(1.0f), glm::radians(m_ZRotation), { 0, 0, 1 });
    m_View = glm::inverse(transform);
    m_ProjectionView = m_Projection * m_View;
    m_CameraBuffer.SetData(&m_ProjectionView, sizeof(m_ProjectionView));
}
