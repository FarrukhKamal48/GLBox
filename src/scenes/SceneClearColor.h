#pragma once
#include "Scene.h"
#include "../GLlog.h"
#include "GL/glew.h"

namespace Scene {

class ClearColor : public Scene {
private:
    float m_ClearColor[4];
    bool pong;
    
public:
    ClearColor() : 
        m_ClearColor { 0, 0, 0, 1.0f }, pong(true) {}
    ~ClearColor() { }
    
    template <typename T>
    T Lerp(T a, T b, T t) {
        return a + (b-a)*t;
    }
    
    void Render() override {
        GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        if (m_ClearColor[0] < 0.05f || m_ClearColor[0] > 0.95f) pong = !pong;
        
        m_ClearColor[0] = Lerp(m_ClearColor[0], 1.0f * pong, 0.1f);
    }
    
};

};
