#pragma once
#include "GL/glew.h"
#include <memory>

#include "../../vendor/glm/ext/matrix_transform.hpp"
#include "../../vendor/glm/ext/matrix_clip_space.hpp"
#include "../Renderer.h"
#include "VertexTypes.h"
#include "MeshData.h"

class InstanceRenderer {
public:
    std::unique_ptr<Shader> InstanceShader;
private:
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<VertexBuffer> m_MeshBuffer;
    std::unique_ptr<VertexBuffer> m_InstanceBuffer;
    glm::mat4 m_Proj;
    glm::mat4 m_View;
    
    unsigned int m_InstanceCount;
    void* m_Data;
    unsigned int m_DataSize;
    
public:
    InstanceRenderer(unsigned int InstanceCount, void* data, const VertexLookup& Lookup) 
        : m_InstanceCount(InstanceCount), m_Data(data), m_DataSize(InstanceCount * Lookup.SizeOfVertex())
    {
        Render::BasicBlend();

        m_VertexArray =  std::make_unique<VertexArray>();
        m_MeshBuffer = std::make_unique<VertexBuffer>(Lookup.MeshData(), Lookup.SizeOfMeshData());
        m_IndexBuffer =  std::make_unique<IndexBuffer>(Lookup.Indicies(), Lookup.CountofIndicies());
        m_InstanceBuffer = std::make_unique<VertexBuffer>(nullptr, m_DataSize, GL_DYNAMIC_DRAW);
        
        m_VertexArray->AddBuffer(*m_MeshBuffer, Lookup.MeshLayout());
        m_VertexArray->AddBuffer(*m_InstanceBuffer, Lookup.VertLayout(1));

        m_Proj = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);
        m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    }
    ~InstanceRenderer() { }
    
    void ShaderInit(const std::string& vertSrcPath, const std::string& fragSrcPath) {
        InstanceShader = std::make_unique<Shader>();
        InstanceShader->Push(GL_VERTEX_SHADER, vertSrcPath);
        InstanceShader->Push(GL_FRAGMENT_SHADER, fragSrcPath);
        InstanceShader->Compile();
        InstanceShader->Bind();
        InstanceShader->SetUniformMat4("u_MVP", m_Proj * m_View);
    }

    void Draw() {
        m_InstanceBuffer->SetData(m_Data, m_DataSize);
        Render::DrawInstanced(*m_VertexArray, *m_IndexBuffer, *InstanceShader, m_InstanceCount);
    }
};
