#pragma once
#include "GL/glew.h"
#include <memory>

#include "../Renderer.h"
#include "../../vendor/glm/ext/matrix_transform.hpp"
#include "../../vendor/glm/ext/matrix_clip_space.hpp"
#include "../VertexBuffer.h"
#include "VertexTypes.h"
#include "MeshData.h"

template<typename MeshType, typename InstanceDataType> class RendererInstanced { };

template<typename InstanceDataType>
class RendererInstanced<QuadData, InstanceDataType> {
public:
    std::unique_ptr<Shader> InstanceShader;
private:
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<VertexBuffer> m_MeshBuffer;
    std::unique_ptr<VertexBuffer> m_InstanceBuffer;
    glm::mat4 m_Proj;
    glm::mat4 m_View;
    
    void* m_Data;
    unsigned int m_DataSize;
    unsigned int m_InstaceCount;
    
public:
    RendererInstanced(void* data, unsigned int count) 
        : m_Data(data), m_DataSize(count * sizeof(InstanceDataType)), m_InstaceCount(count)
    {
        Render::BasicBlend();

        m_VertexArray =  std::make_unique<VertexArray>();
        m_MeshBuffer = std::make_unique<VertexBuffer>(QuadData::GetVerticies(), QuadData::SizeofVerticies());
        m_InstanceBuffer = std::make_unique<VertexBuffer>(nullptr, m_DataSize, GL_DYNAMIC_DRAW);
        m_IndexBuffer =  std::make_unique<IndexBuffer>(QuadData::GetIndicies(), 6);
        
        m_VertexArray->AddBuffer(*m_MeshBuffer, QuadData::Layout());
        m_VertexArray->AddBuffer(*m_InstanceBuffer, InstanceDataType::Layout(1));

        m_Proj = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);
        m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    }
    ~RendererInstanced() { }
    
    void ShaderInit(const std::string& vertSrcPath, const std::string& fragSrcPath) {
        InstanceShader = std::make_unique<Shader>();
        InstanceShader->Push(GL_VERTEX_SHADER, vertSrcPath);
        InstanceShader->Push(GL_FRAGMENT_SHADER, fragSrcPath);
        InstanceShader->Compile();
        InstanceShader->Bind();
        InstanceShader->SetUniformVec4("u_Color", 0.0f, 0.5f, 1.0f, 1.0f);
        InstanceShader->SetUniformMat4("u_MVP", m_Proj * m_View);
    }

    void Draw() {
        Render::Clear(1, 1, 1, 1);
        m_InstanceBuffer->SetData(m_Data, m_DataSize);
        Render::DrawInstanced(*m_VertexArray, *m_IndexBuffer, *InstanceShader, m_InstaceCount);
    }
};
