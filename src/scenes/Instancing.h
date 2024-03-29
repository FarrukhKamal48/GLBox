#pragma once
#include "GL/glew.h"

#include "Scene.h"
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/ext/matrix_clip_space.hpp"
#include "../layer/InstanceRenderer.h"

namespace Scene {

class Instancing : public Scene {
private:
    InstanceRenderer m_Renderer;
    
public:
    Instancing() { }
    ~Instancing() { }

    void Start() override {
        for (int i = 0; i < 4; i++) {
            m_Renderer.GetTransforms()[i] = glm::vec2(100 * (i+1), 100 * i);
        }
    }

    void Update(float dt) override {
        for (int i = 0; i < 4; i++) {
            m_Renderer.GetTransforms()[i].x += (i+1) * 100 * dt;
        }
    }
    
    void Render() override {
        m_Renderer.Draw();
    }
    
};

};
