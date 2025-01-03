#pragma once

#include <glbpch.h>

#include "GLBox/Renderer/Camera.h"
#include "GLBox/Events/MouseEvent.h"
#include "GLBox/Events/WindowEvent.h"

class OrthoCameraController {
public:
    OrthoCameraController(float aspectRatio, float zoomLevel)
        : m_AspectRatio(aspectRatio), m_ZoomLevel(zoomLevel)
        , m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
    { }

    void OnEvent(Event& event);
    void OnResize(uint32_t width, uint32_t height);
    
    void Translate(const glm::vec3& translation) { m_Camera.SetPosition(m_Camera.GetPosition() + translation); }

    OrthoCamera& GetCamera()        { return m_Camera; } 
    float GetAspectRatio()          { return m_AspectRatio; }
    float GetZoomLevel()            { return m_ZoomLevel; }
    const glm::vec2& GetBounds()    { return m_Camera.GetBounds(); }
private:
    bool OnWindowResize(WindowResizeEvent& event);
    bool OnMouseScroll(MouseScrolledEvent& event);
private:
    float m_AspectRatio = 16.0f/9.0f;
    float m_ZoomLevel = 1.0f;
    OrthoCamera m_Camera;
};
