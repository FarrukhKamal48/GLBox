#include "RendererInstanced.h"

InstanceRenderer::InstanceRenderer(const InstanceRenderer& cp) 
    : m_VManager(cp.m_VManager) 
{ }
InstanceRenderer::InstanceRenderer(VertexManager* VManager)
    : m_VManager(VManager)
{ }
InstanceRenderer::InstanceRenderer(unsigned int InstanceCount, void* data, VertexManager* VManager) 
: m_InstanceCount(InstanceCount), m_Data(data), m_DataSize(InstanceCount * VManager->SizeOfObject()), m_VManager(VManager) {
    Init();
}
InstanceRenderer::~InstanceRenderer() {
    delete m_VManager;
}
void InstanceRenderer::SetData(unsigned int InstanceCount, void* data) {
    m_InstanceCount = InstanceCount;
    m_Data = data;
    m_DataSize = InstanceCount * m_VManager->SizeOfObject();
}
void InstanceRenderer::Init() {
    Render::BasicBlend();

    m_VertexArray =  std::make_unique<VertexArray>();
    m_MeshBuffer = std::make_unique<VertexBuffer>(m_VManager->MeshData(), m_VManager->SizeOfMeshData());
    m_IndexBuffer =  std::make_unique<IndexBuffer>(m_VManager->Indicies(), m_VManager->CountofIndicies());
    m_InstanceBuffer = std::make_unique<VertexBuffer>(nullptr, m_DataSize, GL_DYNAMIC_DRAW);
    
    m_VertexArray->AddBuffer(*m_MeshBuffer, m_VManager->MeshLayout());
    m_VertexArray->AddBuffer(*m_InstanceBuffer, m_VManager->VertLayout(1));

    m_Proj = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);
    m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}
void InstanceRenderer::CreateShader(const std::string& vertSrcPath, const std::string& fragSrcPath) {
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


template <class Object>
static unsigned int AllocateObj(unsigned int count, void (*ConfigureShader)(InstanceRenderer&), VertexManager* VManager, 
                                  std::vector<Object>& instances, InstanceRenderer*& renderer) {
    instances.insert(instances.end(), count, Object());
    if (!renderer) {
        Renderers.emplace_back(VManager);
        renderer = &Renderers.back();
        renderer->SetData(instances.size(), instances.data());
        renderer->Init();
        ConfigureShader(*renderer);
    } else
        renderer->SetData(instances.size(), instances.data());
    return instances.size() - count;
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
    return &m_Instances[AllocateObject(count, ConfigureShader)];
}


namespace Render {
    void DrawAllInstanced() {
        for (int i=0; i < (int)Renderers.size(); i++) {
            Renderers[i].Draw();
        }
    } 
}

