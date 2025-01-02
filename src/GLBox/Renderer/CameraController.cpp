#include "GLBox/Renderer/CameraController.h"

void OrthoCameraController::OnEvent(Event& event) {
    EventDispacher dispatcher(event);
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
    dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OnMouseScroll));
}

bool OrthoCameraController::OnWindowResize(WindowResizeEvent& event) {
    m_AspectRatio = (float)event.GetWidth() / event.GetHeight();
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    return false;
}
bool OrthoCameraController::OnMouseScroll(MouseScrolledEvent& event) {
    m_ZoomLevel -= event.GetYOffset();
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    return false;
}
