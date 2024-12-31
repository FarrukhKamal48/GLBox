#pragma once

#include "GLBox/Events/Event.h"

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(const float x, const float y)
        : m_MouseX(x), m_MouseY(y) 
    { }

    float GetX() const { return m_MouseX; }
    float GetY() const { return m_MouseY; }

    EVENT_CLASS_TYPE(MouseMoved);
    EVENT_CLASS_CATAGORY(EventCatagoryMouse | EventCatagoryInput)
private:
    float m_MouseX;
    float m_MouseY;
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(const float xOffset, const float yOffset)
        : m_XOffset(xOffset), m_YOffset(yOffset) 
    { }

    float GetXOffset() const { return m_XOffset; }
    float GetYOffset() const { return m_YOffset; }

    EVENT_CLASS_TYPE(MouseScrolled);
    EVENT_CLASS_CATAGORY(EventCatagoryMouse | EventCatagoryInput);
private:
    float m_XOffset;
    float m_YOffset;
};

class MouseButtonEvent : public Event {
public:
    MouseCode GetMouseButton() const { return m_Button; }

    EVENT_CLASS_CATAGORY(EventCatagoryMouse | EventCatagoryInput | EventCatagoryMouseButton);
protected:
    MouseButtonEvent(const MouseCode button)
        : m_Button(button) 
    { }

    MouseCode m_Button;
};

class MousePressedEvent : public MouseButtonEvent {
public:
    MousePressedEvent(const MouseCode button)
        : MouseButtonEvent(button) 
    { }

    EVENT_CLASS_TYPE(MouseButtonPressed);
};

class MouseReleasedEvent : public MouseButtonEvent {
public:
    MouseReleasedEvent(const MouseCode button) : MouseButtonEvent(button) { }

    EVENT_CLASS_TYPE(MouseButtonReleased)
};

