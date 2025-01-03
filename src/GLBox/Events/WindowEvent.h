#pragma once

#include <glbpch.h>
#include "GLBox/Events/Event.h"

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(uint32_t Width, uint32_t Height) 
        : m_Width(Width), m_Height(Height)
    {}

    uint32_t GetWidth() const { return m_Width; }
    uint32_t GetHeight() const { return m_Height; }

    EVENT_CLASS_TYPE(WindowResize);
    EVENT_CLASS_CATAGORY(EventCatagoryWindow);

private:
    uint32_t m_Width;
    uint32_t m_Height;
};

class WindowMinimizeEvent : public Event {
public:
    WindowMinimizeEvent(bool minimized) : m_IsMinimized(minimized) { }

    bool IsMinimized() const { return m_IsMinimized; }
    
    EVENT_CLASS_TYPE(WindowMinimize);
    EVENT_CLASS_CATAGORY(EventCatagoryWindow);
private:
    bool m_IsMinimized;
};

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() = default;

    EVENT_CLASS_TYPE(WindowClose);
    EVENT_CLASS_CATAGORY(EventCatagoryWindow);
};

