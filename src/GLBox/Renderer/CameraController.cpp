#include <glbpch.h>
#include "GLBox/Renderer/CameraController.h"

void OrthoCameraController::OnEvent(Event& event) {
    EventDispacher dispatcher(event);
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
    dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OnMouseScroll));
}

void OrthoCameraController::OnResize(uint32_t width, uint32_t height) {
    m_AspectRatio = (float)width / height;
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}

bool OrthoCameraController::OnWindowResize(WindowResizeEvent& event) {
    OnResize(event.GetWidth(), event.GetHeight());
    return false;
}
bool OrthoCameraController::OnMouseScroll(MouseScrolledEvent& event) {
    m_ZoomLevel -= event.GetYOffset() * 0.05f;
    m_ZoomLevel = std::max(0.1f, m_ZoomLevel);
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    return false;
}
