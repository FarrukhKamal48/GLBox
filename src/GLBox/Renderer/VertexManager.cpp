#include <glbpch.h>

#include "GLBox/Renderer/Renderer.h"
#include "GLBox/Renderer/RendererInstanced.h"

static std::vector<InstanceRenderer> Renderers;

template <class Object>
static uint32_t AllocateObj(uint32_t count, std::function<void(InstanceRenderer&)> ConfigureShader, VertexManager* VManager, 
                                  std::vector<Object>& instances, int& rendererI) {
    uint32_t lastSize = instances.size();
    instances.insert(instances.end(), count, Object());
    if (rendererI == -1) {
        rendererI = Renderers.size();
        Renderers.emplace_back(instances.size(), instances.data(), VManager);
        ConfigureShader(Renderers[rendererI]);
    } else
        Renderers[rendererI].SetData(instances.size(), instances.data());
    delete VManager;
    return lastSize;
}


Pos_Scale_Col_Quad::Pos_Scale_Col_Quad() : position(0), scale(0), color(0) { }
Pos_Scale_Col_Quad::~Pos_Scale_Col_Quad() { }

const VertexBufferLayout Pos_Scale_Col_Quad_Manager::MeshLayout() const { 
    VertexBufferLayout MeshLayout;
    MeshLayout.Push<float>(2);
    MeshLayout.Push<float>(2);
    return MeshLayout; 
}
VertexBufferLayout Pos_Scale_Col_Quad_Manager::VertLayout(uint32_t divisor) const {
    VertexBufferLayout layout;
    layout.Push<float>(2, divisor);
    layout.Push<float>(2, divisor);
    layout.Push<float>(4, divisor);
    return layout;
}
uint32_t Pos_Scale_Col_Quad_Manager::SizeOfObject()                     const { return sizeof(Pos_Scale_Col_Quad); }
const std::vector<float>& Pos_Scale_Col_Quad_Manager::MeshData()            const { return m_Mesh; }
const std::vector<uint32_t>& Pos_Scale_Col_Quad_Manager::Indicies()     const { return m_Indicies; }
const uint32_t Pos_Scale_Col_Quad_Manager::AllocateObject(uint32_t count, std::function<void(InstanceRenderer&)> ConfigureShader) const {
    return AllocateObj(count, ConfigureShader, new Pos_Scale_Col_Quad_Manager(), m_Instances, m_RendererI);
}
Pos_Scale_Col_Quad& Pos_Scale_Col_Quad_Manager::operator[](uint32_t i) {
    assert(i >= 0 && i < m_Instances.size() 
           && "Invalid index into QuadTransform_Manager::m_Instances");
    return m_Instances[i]; 
}



QuadTransform::QuadTransform() : position(0), scale(0), rotation(0), color(0) { }
QuadTransform::~QuadTransform() { }

const VertexBufferLayout QuadTransform_Manager::MeshLayout() const { 
    VertexBufferLayout MeshLayout;
    MeshLayout.Push<float>(2);
    MeshLayout.Push<float>(2);
    return MeshLayout; 
}
VertexBufferLayout QuadTransform_Manager::VertLayout(uint32_t divisor) const {
    VertexBufferLayout layout;
    layout.Push<float>(3, divisor);
    layout.Push<float>(2, divisor);
    layout.Push<float>(1, divisor);
    layout.Push<float>(4, divisor);
    return layout;
}
uint32_t QuadTransform_Manager::SizeOfObject()                      const { return sizeof(QuadTransform); }
const std::vector<float>& QuadTransform_Manager::MeshData()             const { return m_Mesh; }
const std::vector<uint32_t>& QuadTransform_Manager::Indicies()      const { return m_Indicies; }
const uint32_t QuadTransform_Manager::AllocateObject(uint32_t count, std::function<void(InstanceRenderer&)> ConfigureShader) const {
    return AllocateObj(count, ConfigureShader, new QuadTransform_Manager(), m_Instances, m_RendererI);
}
QuadTransform& QuadTransform_Manager::operator[](uint32_t i) {
    assert(i >= 0 && i < m_Instances.size() 
           && "Invalid index into QuadTransform_Manager::m_Instances");
    return m_Instances[i]; 
}


void Renderer::DrawAllInstanced() {
    for (int i=0; i < (int)Renderers.size(); i++) {
        Renderers[i].Draw();
    }
} 

