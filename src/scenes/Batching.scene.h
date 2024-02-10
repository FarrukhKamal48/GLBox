#pragma once
#include <cstring>
#include <memory>
#include "GL/glew.h"

#include "Scene.h"
#include "../layer/Batching.h"

namespace Scene {

class Batching : public Scene {
private:
    Primative::Circle m_Circles[2];
    Batch m_Batch;
public:
    Batching() : 
        m_Batch(2) 
    { 
    }
    ~Batching() { }

    void Start() override {
    }

    void Update(float dt) override {
        m_Batch.ClearData();
        m_Batch.SetData(m_Circles);
    }
    
    void Render() override {
        m_Batch.Draw();
    }
    
};

};

