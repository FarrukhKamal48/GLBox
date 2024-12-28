#include "Core/Renderer.h"
#include "Core/Instancing/RendererInstanced.h"
#include "Core/Application.h"

#define ResizeMultiplier (float)1.5f

InstanceRenderer::InstanceRenderer(const InstanceRenderer& cp) 
    : m_VManager(cp.m_VManager) 
{ }
InstanceRenderer::InstanceRenderer(VertexManager* VManager)
    : m_VManager(VManager)
{ }
InstanceRenderer::InstanceRenderer(unsigned int InstanceCount, void* data, VertexManager* VManager) 
    : m_InstanceCount(InstanceCount), m_TargetCount(InstanceCount * ResizeMultiplier)
    , m_Data(data), m_AllocatedDataSize(InstanceCount * VManager->SizeOfObject()), m_VManager(VManager) {
    Init();
}
InstanceRenderer::~InstanceRenderer() {
    delete m_VManager;
}
void InstanceRenderer::SetData(unsigned int InstanceCount, void* data) {
    m_Data = data;
    m_InstanceCount = InstanceCount;
    m_OccupiedDataSize = m_InstanceCount * m_VManager->SizeOfObject();
    m_AllocatedDataSize = m_TargetCount * m_VManager->SizeOfObject();
}
void InstanceRenderer::Init() {
    Render::BasicBlend();

    m_VertexArray =  std::make_unique<VertexArray>();
    m_MeshBuffer = std::make_unique<VertexBuffer>(m_VManager->MeshData(), m_VManager->SizeOfMeshData());
    m_IndexBuffer =  std::make_unique<IndexBuffer>(m_VManager->Indicies(), m_VManager->CountofIndicies());
    
    m_VertexArray->AddBuffer(*m_MeshBuffer, m_VManager->MeshLayout());

    m_Proj = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f);
    m_View = glm::translate(glm::mat4(1.0f), -glm::vec3(0.0f, 0.0f, 0.0f));
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
    if (m_InstanceBuffer == nullptr) {
        m_InstanceBuffer = std::make_unique<VertexBuffer>(m_Data, m_AllocatedDataSize, GL_DYNAMIC_DRAW);
        m_VertexArray->AddBuffer(*m_InstanceBuffer, m_VManager->VertLayout(1));
    } 
    if (m_InstanceCount >= m_TargetCount) {
        m_TargetCount = m_InstanceCount * ResizeMultiplier;
        m_AllocatedDataSize = m_TargetCount * m_VManager->SizeOfObject();
        
        m_VertexArray.reset(new VertexArray());
        m_InstanceBuffer.reset(new VertexBuffer(m_Data, m_AllocatedDataSize, GL_DYNAMIC_DRAW));
        
        m_VertexArray->AddBuffer(*m_MeshBuffer, m_VManager->MeshLayout());
        m_VertexArray->AddBuffer(*m_InstanceBuffer, m_VManager->VertLayout(1));
    }
    m_InstanceBuffer->SetData(m_Data, m_OccupiedDataSize);
    Render::DrawInstanced(*m_VertexArray, *m_IndexBuffer, *InstanceShader, m_InstanceCount);
}

