#include <glm/ext/matrix_clip_space.hpp>

#include "GLBox/Renderer/RenderCommands.h"
#include "GLBox/Renderer/RendererInstanced.h"

#define ResizeMultiplier (float)2.0f

InstanceRenderer::InstanceRenderer(const InstanceRenderer& cp) 
    : InstanceShader(cp.InstanceShader), m_VertexArray(cp.m_VertexArray), m_IndexBuffer(cp.m_IndexBuffer)
    , m_MeshBuffer(cp.m_MeshBuffer) , m_InstanceBuffer(cp.m_InstanceBuffer) 
    , m_InstanceCount(cp.m_InstanceCount), m_TargetCount(cp.m_TargetCount), m_Data(cp.m_Data)
    , m_OccupiedDataSize(cp.m_OccupiedDataSize), m_AllocatedDataSize(cp.m_AllocatedDataSize)
    , m_VData(cp.m_VData), m_MeshLayout(cp.m_MeshLayout), m_VertLayout(cp.m_VertLayout)
{ }
// InstanceRenderer::InstanceRenderer(VertexManager* VManager)
//     : m_VData(VManager), m_MeshLayout(VManager->MeshLayout()), m_VertLayout(VManager->VertLayout(1))
// { delete VManager; }
InstanceRenderer::InstanceRenderer(unsigned int InstanceCount, void* data, VertexManager* VManager) 
    : m_InstanceCount(InstanceCount), m_TargetCount(InstanceCount * ResizeMultiplier) , m_Data(data)
    , m_OccupiedDataSize(InstanceCount * VManager->SizeOfObject())
    , m_AllocatedDataSize(InstanceCount * ResizeMultiplier * VManager->SizeOfObject())
    , m_VData(VManager), m_MeshLayout(VManager->MeshLayout()), m_VertLayout(VManager->VertLayout(1)) {
    Init();
}
InstanceRenderer::~InstanceRenderer() {
}
void InstanceRenderer::SetData(unsigned int InstanceCount, void* data) {
    m_Data = data;
    m_InstanceCount = InstanceCount;
    m_OccupiedDataSize = m_InstanceCount * m_VData.SizeOfObject;
    m_AllocatedDataSize = m_TargetCount * m_VData.SizeOfObject;
}
void InstanceRenderer::Init() {
    RenderCommand::BasicBlend();

    m_VertexArray = std::make_shared<VertexArray>();
    m_MeshBuffer = std::make_shared<VertexBuffer>(m_VData.MeshData.data(), m_VData.SizeOfMeshData);
    m_IndexBuffer = std::make_shared<IndexBuffer>(m_VData.Indicies.data(), m_VData.CountofIndicies);
    
    m_VertexArray->AddBuffer(*m_MeshBuffer, m_MeshLayout);
}
void InstanceRenderer::CreateShader(const std::string& vertSrcPath, const std::string& fragSrcPath) {
    InstanceShader = std::make_shared<Shader>();
    InstanceShader->Push(GL_VERTEX_SHADER, vertSrcPath);
    InstanceShader->Push(GL_FRAGMENT_SHADER, fragSrcPath);
    InstanceShader->Compile();
    InstanceShader->Bind();
    InstanceShader->SetUniformMat4("u_MVP", RenderCommand::GetRenderData().ProjectionMatix * 
                                   RenderCommand::GetRenderData().ViewMatrix);
}
void InstanceRenderer::Draw() {
    if (m_InstanceCount >= m_TargetCount) {
        m_TargetCount = m_InstanceCount * ResizeMultiplier;
        m_AllocatedDataSize = m_TargetCount * m_VData.SizeOfObject;

        m_VertexArray = std::make_shared<VertexArray>();
        m_InstanceBuffer = std::make_shared<VertexBuffer>(m_Data, m_AllocatedDataSize, GL_DYNAMIC_DRAW);

        m_VertexArray->AddBuffer(*m_MeshBuffer, m_MeshLayout);
        m_VertexArray->AddBuffer(*m_InstanceBuffer, m_VertLayout);
    }
    else if (m_InstanceBuffer == nullptr) {
        m_InstanceBuffer = std::make_shared<VertexBuffer>(m_Data, m_AllocatedDataSize, GL_DYNAMIC_DRAW);
        m_VertexArray->AddBuffer(*m_InstanceBuffer, m_VertLayout);
    } 
    m_InstanceBuffer->SetData(m_Data, m_OccupiedDataSize);
    // if (InstanceShader)
        RenderCommand::DrawInstanced(*m_VertexArray, *m_IndexBuffer, *InstanceShader, m_InstanceCount);
}

void InstanceRenderer::FetchMatricies() {
    InstanceShader->Bind();
    InstanceShader->SetUniformMat4("u_MVP", RenderCommand::GetRenderData().ProjectionMatix * 
                                   RenderCommand::GetRenderData().ViewMatrix);
}

