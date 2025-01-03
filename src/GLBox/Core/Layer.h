#pragma once

#include <glbpch.h>
#include "GLBox/Events/Event.h"

class Layer {
public:
    Layer(const std::string& name) : m_DebugName(name) {};
    virtual ~Layer() {};

    virtual void OnEvent(Event& event) {};
    
    virtual void OnAttach() {};
    virtual void OnDetach() {};
    virtual void OnUpdate(float dt) {};
    virtual void OnRender() {};
    virtual void OnImGuiRender() {};

    const std::string& GetName() { return m_DebugName; }
private:
    std::string m_DebugName;
};
