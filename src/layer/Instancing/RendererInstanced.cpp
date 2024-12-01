#include "RendererInstanced.h"

InstanceRenderer::InstanceRenderer(const InstanceRenderer& cp) 
    : m_Lookup(cp.m_Lookup) 
{ }
InstanceRenderer::InstanceRenderer(VertexLookup* Lookup) 
    : m_Lookup(Lookup) 
{ }
InstanceRenderer::InstanceRenderer(unsigned int InstanceCount, void* data, VertexLookup* Lookup) 
: m_InstanceCount(InstanceCount), m_Data(data), m_DataSize(InstanceCount * Lookup->SizeOfVertex()), m_Lookup(Lookup) {
    Init();
}
InstanceRenderer::~InstanceRenderer() {
    delete m_Lookup;
}
void InstanceRenderer::SetData(unsigned int InstanceCount, void* data) {
    m_InstanceCount = InstanceCount;
    m_Data = data;
    m_DataSize = InstanceCount * m_Lookup->SizeOfVertex();
}
void InstanceRenderer::Init() {
    Render::BasicBlend();

    m_VertexArray =  std::make_unique<VertexArray>();
    m_MeshBuffer = std::make_unique<VertexBuffer>(m_Lookup->MeshData(), m_Lookup->SizeOfMeshData());
    m_IndexBuffer =  std::make_unique<IndexBuffer>(m_Lookup->Indicies(), m_Lookup->CountofIndicies());
    m_InstanceBuffer = std::make_unique<VertexBuffer>(nullptr, m_DataSize, GL_DYNAMIC_DRAW);
    
    m_VertexArray->AddBuffer(*m_MeshBuffer, m_Lookup->MeshLayout());
    m_VertexArray->AddBuffer(*m_InstanceBuffer, m_Lookup->VertLayout(1));

    m_Proj = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);
    m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}
void InstanceRenderer::ShaderInit(const std::string& vertSrcPath, const std::string& fragSrcPath) {
    InstanceShader = std::make_unique<Shader>();
    InstanceShader->Push(GL_VERTEX_SHADER, vertSrcPath);
    InstanceShader->Push(GL_FRAGMENT_SHADER, fragSrcPath);
    InstanceShader->Compile();
    InstanceShader->Bind();
    InstanceShader->SetUniformMat4("u_MVP", m_Proj * m_View);
}
void InstanceRenderer::Draw() {
    m_InstanceBuffer->SetData(m_Data, m_DataSize);
    Render::DrawInstanced(*m_VertexArray, *m_IndexBuffer, *InstanceShader, m_InstanceCount);
}


template <class Object, class Lookup>
ObjectPool<Object> InstantiateObj(std::vector<Object>& instances, unsigned int count, InstanceRenderer*& renderer, Lookup* lookup) {
    instances.insert(instances.end(), count, Object());
    if (!renderer) {
        Renderers.emplace_back(lookup);
        renderer = &Renderers.back();
    }
    renderer->SetData(instances.size(), instances.data());
    return ObjectPool<Object>(&instances[instances.size()-count], count);
}

Pos_Scale_Col_Quad::Pos_Scale_Col_Quad() : position(0), scale(0), color(0) { }
Pos_Scale_Col_Quad::~Pos_Scale_Col_Quad() { }
ObjectPool<Pos_Scale_Col_Quad> Pos_Scale_Col_Quad::Instantiate(unsigned int count) {
    return InstantiateObj(m_Instances, count, m_Renderer, new Pos_Scale_Col_Quad_Lookup());
}
std::vector<Pos_Scale_Col_Quad>& Pos_Scale_Col_Quad::Instances() {
    return m_Instances;
}

VertexBufferLayout Pos_Scale_Col_Quad_Lookup::VertLayout(unsigned int divisor) const {
    VertexBufferLayout layout;
    layout.Push<float>(2, divisor);
    layout.Push<float>(2, divisor);
    layout.Push<float>(4, divisor);
    return layout;
}
const VertexBufferLayout Pos_Scale_Col_Quad_Lookup::MeshLayout() const { 
    VertexBufferLayout MeshLayout;
    MeshLayout.Push<float>(2);
    MeshLayout.Push<float>(2);
    return MeshLayout; 
}
unsigned int Pos_Scale_Col_Quad_Lookup::SizeOfVertex()          const { return sizeof(Pos_Scale_Col_Quad); }
const float* Pos_Scale_Col_Quad_Lookup::MeshData()              const { return m_Mesh; }
const unsigned int* Pos_Scale_Col_Quad_Lookup::Indicies()       const { return m_Indicies; }
const unsigned int Pos_Scale_Col_Quad_Lookup::SizeOfMeshData()  const { return sizeof(m_Mesh); }
const unsigned int Pos_Scale_Col_Quad_Lookup::CountofIndicies() const { return sizeof(m_Indicies); }



namespace Render {
    void InitAllInstanced() {
        for (int i=0; i < (int)Renderers.size(); i++) {
            Renderers[i].Init();
            Renderers[i].ShaderInit("assets/shaders/instancing/BasicColorScale.vert", 
                                    "assets/shaders/instancing/CircleInRectColor.frag");        
            Renderers[i].InstanceShader->SetUniform<float>("u_CullRadius", 0.5f);
            Renderers[i].InstanceShader->SetUniform<float>("u_EdgeSmooth", 1.2f);               
        }
    } 
    void InitAllInstanced(void (*ShaderInit)(InstanceRenderer&)) {
        for (int i=0; i < (int)Renderers.size(); i++) {
            Renderers[i].Init();
            ShaderInit(Renderers[i]);
        }
    } 
    void DrawAllInstanced() {
        for (int i=0; i < (int)Renderers.size(); i++) {
            Renderers[i].Draw();
        }
    } 
}

