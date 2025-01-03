#pragma once
#include "GLBox/Core/Base.h"

enum class EventType {
    None = 0,
    WindowClose, WindowResize, WindowMinimize, WindowFocus, WindowLostFocus, WindowMoved,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled    
};
enum EventCatagory {
    None = 0,
    EventCatagoryWindow         = BIT(0),
    EventCatagoryInput          = BIT(1),
    EventCatagoryKeyboard       = BIT(2),
    EventCatagoryMouse          = BIT(3),
    EventCatagoryMouseButton    = BIT(4),
};

class Event {
public:
    virtual ~Event() = default;
    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCatagory() const = 0;

    bool Handled = false;

    bool IsInCatagory(EventCatagory catagory) {
        return GetCatagory() & catagory;
    }
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
                                virtual EventType GetEventType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATAGORY(catagory) virtual int GetCatagory() const override { return catagory; }


class EventDispacher {
public:
    EventDispacher(Event& event) : m_Event(event) {}
    ~EventDispacher() = default;
    
    template<typename EventT, typename CallBackFnT>
    bool Dispatch(const CallBackFnT& func) {
        if (m_Event.GetEventType() == EventT::GetStaticType()) {
            m_Event.Handled |= func(static_cast<EventT&>(m_Event));
            return true;
        }
        return false;
    }
private:
    Event& m_Event;
};


