#include "Core/Instancing/RendererInstanced.h"
#include <functional>

static std::vector<InstanceRenderer> Renderers;

template <class Object>
static unsigned int AllocateObj(unsigned int count, std::function<void(InstanceRenderer&)> ConfigureShader, VertexManager* VManager, 
                                  std::vector<Object>& instances, int& rendererI) {
    unsigned int lastSize = instances.size();
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
VertexBufferLayout Pos_Scale_Col_Quad_Manager::VertLayout(unsigned int divisor) const {
    VertexBufferLayout layout;
    layout.Push<float>(2, divisor);
    layout.Push<float>(2, divisor);
    layout.Push<float>(4, divisor);
    return layout;
}
unsigned int Pos_Scale_Col_Quad_Manager::SizeOfObject()                     const { return sizeof(Pos_Scale_Col_Quad); }
const std::vector<float>& Pos_Scale_Col_Quad_Manager::MeshData()            const { return m_Mesh; }
const std::vector<unsigned int>& Pos_Scale_Col_Quad_Manager::Indicies()     const { return m_Indicies; }
const unsigned int Pos_Scale_Col_Quad_Manager::AllocateObject(unsigned int count, std::function<void(InstanceRenderer&)> ConfigureShader) const {
    return AllocateObj(count, ConfigureShader, new Pos_Scale_Col_Quad_Manager(), m_Instances, m_RendererI);
}



QuadTransform::QuadTransform() : position(0), scale(0), rotation(0), color(0) { }
QuadTransform::~QuadTransform() { }

const VertexBufferLayout QuadTransform_Manager::MeshLayout() const { 
    VertexBufferLayout MeshLayout;
    MeshLayout.Push<float>(2);
    MeshLayout.Push<float>(2);
    return MeshLayout; 
}
VertexBufferLayout QuadTransform_Manager::VertLayout(unsigned int divisor) const {
    VertexBufferLayout layout;
    layout.Push<float>(2, divisor);
    layout.Push<float>(2, divisor);
    layout.Push<float>(1, divisor);
    layout.Push<float>(4, divisor);
    return layout;
}
unsigned int QuadTransform_Manager::SizeOfObject()                      const { return sizeof(QuadTransform); }
const std::vector<float>& QuadTransform_Manager::MeshData()             const { return m_Mesh; }
const std::vector<unsigned int>& QuadTransform_Manager::Indicies()      const { return m_Indicies; }
const unsigned int QuadTransform_Manager::AllocateObject(unsigned int count, std::function<void(InstanceRenderer&)> ConfigureShader) const {
    return AllocateObj(count, ConfigureShader, new QuadTransform_Manager(), m_Instances, m_RendererI);
}


namespace Render {
    void DrawAllInstanced() {
        for (int i=0; i < (int)Renderers.size(); i++) {
            Renderers[i].Draw();
        }
    } 
}

