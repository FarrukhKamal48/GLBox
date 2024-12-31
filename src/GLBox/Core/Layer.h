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
    virtual void Update(float dt) {};
    virtual void Render() {};
    virtual void ImGuiRender() {};

    const std::string& GetName() { return m_DebugName; }
private:
    std::string m_DebugName;
};
