#pragma once

#include "GLBox/Events/Event.h"
#include "GLBox/Events/MouseEvent.h"
#include "GLBox/Events/WindowEvent.h"
#include "GLBox/Renderer/Camera.h"

class OrthoCameraController {
public:
    OrthoCameraController(float aspectRatio, float zoomLevel)
        : m_AspectRatio(aspectRatio), m_ZoomLevel(zoomLevel)
        , m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
    { }

    void OnEvent(Event& event) {
        EventDispacher dispatcher(event);
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OnMouseScroll));
    }

    OrthoCamera& GetCamera() { return m_Camera; } 
    float GetAspectRatio() { return m_AspectRatio; }
    float GetZoomLevel() { return m_ZoomLevel; }
private:
    bool OnWindowResize(WindowResizeEvent& event) {
        m_AspectRatio = (float)event.GetWidth() / event.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
    bool OnMouseScroll(MouseScrolledEvent& event) {
        m_ZoomLevel -= event.GetYOffset();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
private:
    float m_AspectRatio = 16.0f/9.0f;
    float m_ZoomLevel = 1.0f;
    OrthoCamera m_Camera;
};
