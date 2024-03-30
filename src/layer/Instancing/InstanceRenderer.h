#pragma once
#include "GL/glew.h"
#include <memory>

#include "../Renderer.h"
#include "../../vendor/glm/ext/matrix_transform.hpp"
#include "../../vendor/glm/ext/matrix_clip_space.hpp"
#include "../VertexBuffer.h"
#include "Quad.h"

namespace Instancing {

template<typename MeshType> class Renderer { };

template<>
class Renderer<Quad> {
public:
    std::unique_ptr<Shader> InstanceShader;
private:
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<VertexBuffer> m_TransBuffer;
    glm::mat4 m_Proj;
    glm::mat4 m_View;
    
    float m_Length = 10;
    void* m_Data;
    unsigned int m_DataSize;
    unsigned int m_InstaceCount;
    
public:
    Renderer(void* data, unsigned int size, unsigned int count) 
        : m_Data(data), m_DataSize(size), m_InstaceCount(count)
    {
        Render::BasicBlend();

        m_VertexArray =  std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(Quad::GetVerticies(), Quad::SizeofVerticies());
        m_TransBuffer = std::make_unique<VertexBuffer>(nullptr, m_DataSize, GL_DYNAMIC_DRAW);
        m_IndexBuffer =  std::make_unique<IndexBuffer>(Quad::GetIndicies(), 6);
        
        m_VertexArray->AddBuffer(*m_VertexBuffer, Quad::Layout());

        VertexBufferLayout translateLayout;
        translateLayout.Push<float>(2, 1);
        m_VertexArray->AddBuffer(*m_TransBuffer, translateLayout);

        m_Proj = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);
        m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    }
    ~Renderer() { }
    
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
        m_TransBuffer->SetData(m_Data, m_DataSize);
        Render::DrawInstanced(*m_VertexArray, *m_IndexBuffer, *InstanceShader, m_InstaceCount);
    }
};
}
