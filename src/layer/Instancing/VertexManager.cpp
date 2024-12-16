#include "RendererInstanced.h"
#include <iostream>

static std::vector<InstanceRenderer> Renderers;

template <class Object>
static unsigned int AllocateObj(unsigned int count, void (*ConfigureShader)(InstanceRenderer&), VertexManager* VManager, 
                                  std::vector<Object>& instances, InstanceRenderer*& renderer) {
    unsigned int lastSize = instances.size();
    instances.insert(instances.end(), count, Object());
    if (!renderer) {
        Renderers.emplace_back(instances.size(), instances.data(), VManager);
        renderer = &Renderers.back();
        renderer->Init();
        ConfigureShader(*renderer);
    } else
        renderer->SetData(instances.size(), instances.data());
    return lastSize;
}


Pos_Scale_Col_Quad::Pos_Scale_Col_Quad() : position(0), scale(0), color(0) { }
Pos_Scale_Col_Quad::~Pos_Scale_Col_Quad() { }

VertexBufferLayout Pos_Scale_Col_Quad_Manager::VertLayout(unsigned int divisor) const {
    VertexBufferLayout layout;
    layout.Push<float>(2, divisor);
    layout.Push<float>(2, divisor);
    layout.Push<float>(4, divisor);
    return layout;
}
const VertexBufferLayout Pos_Scale_Col_Quad_Manager::MeshLayout() const { 
    VertexBufferLayout MeshLayout;
    MeshLayout.Push<float>(2);
    MeshLayout.Push<float>(2);
    return MeshLayout; 
}
unsigned int Pos_Scale_Col_Quad_Manager::SizeOfObject()             const { return sizeof(Pos_Scale_Col_Quad); }
const float* Pos_Scale_Col_Quad_Manager::MeshData()                 const { return m_Mesh; }
const unsigned int* Pos_Scale_Col_Quad_Manager::Indicies()          const { return m_Indicies; }
const unsigned int Pos_Scale_Col_Quad_Manager::SizeOfMeshData()     const { return sizeof(m_Mesh); }
const unsigned int Pos_Scale_Col_Quad_Manager::CountofIndicies()    const { return sizeof(m_Indicies); }
const void* Pos_Scale_Col_Quad_Manager::GetInstances()              const { return &m_Instances; }
const void* Pos_Scale_Col_Quad_Manager::GetRenderer()               const { return m_Renderer; }
const unsigned int Pos_Scale_Col_Quad_Manager::AllocateObject(unsigned int count, void (*ConfigureShader)(InstanceRenderer&)) const {
    return AllocateObj(count, ConfigureShader, new Pos_Scale_Col_Quad_Manager(), m_Instances, m_Renderer);
}
Pos_Scale_Col_Quad* Pos_Scale_Col_Quad_Manager::Instantiate(unsigned int count, void (*ConfigureShader)(InstanceRenderer&)) {
    int index = AllocateObject(count, ConfigureShader);
    std::cout << index << ", " << m_Instances.size() << '\n';
    return &m_Instances[index];
}
Pos_Scale_Col_Quad* Pos_Scale_Col_Quad_Manager::At(unsigned int index) {
    return &m_Instances[index];
}


namespace Render {
    void DrawAllInstanced() {
        for (int i=0; i < (int)Renderers.size(); i++) {
            Renderers[i].Draw();
        }
    } 
}

