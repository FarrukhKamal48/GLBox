#include "Core/Instancing/RendererInstanced.h"

static std::vector<InstanceRenderer> Renderers;

template <class Object>
static unsigned int AllocateObj(unsigned int count, void (*ConfigureShader)(InstanceRenderer&), VertexManager* VManager, 
                                  std::vector<Object>& instances, int& rendererI) {
    unsigned int lastSize = instances.size();
    instances.insert(instances.end(), count, Object());
    if (rendererI == -1) {
        rendererI = Renderers.size();
        Renderers.emplace_back(instances.size(), instances.data(), VManager);
        Renderers[rendererI].Init();
        ConfigureShader(Renderers[rendererI]);
    } else {
        Renderers[rendererI].SetData(instances.size(), instances.data());
        delete VManager;
    }
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
const unsigned int Pos_Scale_Col_Quad_Manager::AllocateObject(unsigned int count, void (*ConfigureShader)(InstanceRenderer&)) const {
    return AllocateObj(count, ConfigureShader, new Pos_Scale_Col_Quad_Manager(), m_Instances, m_RendererI);
}



QuadTransform::QuadTransform() : position(0), scale(0), rotation(0), color(0) { }
QuadTransform::~QuadTransform() { }

VertexBufferLayout QuadTransform_Manager::VertLayout(unsigned int divisor) const {
    VertexBufferLayout layout;
    layout.Push<float>(2, divisor);
    layout.Push<float>(2, divisor);
    layout.Push<float>(1, divisor);
    layout.Push<float>(4, divisor);
    return layout;
}
const VertexBufferLayout QuadTransform_Manager::MeshLayout() const { 
    VertexBufferLayout MeshLayout;
    MeshLayout.Push<float>(2);
    MeshLayout.Push<float>(2);
    return MeshLayout; 
}
unsigned int QuadTransform_Manager::SizeOfObject()             const { return sizeof(QuadTransform); }
const float* QuadTransform_Manager::MeshData()                 const { return m_Mesh; }
const unsigned int* QuadTransform_Manager::Indicies()          const { return m_Indicies; }
const unsigned int QuadTransform_Manager::SizeOfMeshData()     const { return sizeof(m_Mesh); }
const unsigned int QuadTransform_Manager::CountofIndicies()    const { return sizeof(m_Indicies); }
const unsigned int QuadTransform_Manager::AllocateObject(unsigned int count, void (*ConfigureShader)(InstanceRenderer&)) const {
    return AllocateObj(count, ConfigureShader, new QuadTransform_Manager(), m_Instances, m_RendererI);
}


namespace Render {
    void DrawAllInstanced() {
        for (int i=0; i < (int)Renderers.size(); i++) {
            Renderers[i].Draw();
        }
    } 
}

