#pragma once

#include "GLBox/Events/Event.h"

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(unsigned int Width, unsigned int Height) 
        : m_Width(Width), m_Height(Height)
    {}

    unsigned int GetWidth() const { return m_Width; }
    unsigned int GetHeight() const { return m_Height; }

    EVENT_CLASS_TYPE(WindowResize);
    EVENT_CLASS_CATAGORY(EventCatagoryWindow);

private:
    unsigned int m_Width;
    unsigned int m_Height;
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

