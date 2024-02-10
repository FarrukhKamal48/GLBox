#pragma once
#include "../primatives/Circle.primative.h"
#include "../layer/Renderer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <vector>
#include <memory>

class Batch {
private:
    int m_BatchCount;
    std::vector<Vertex> m_Data;
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<Shader> m_Shader;
public:
    Batch (unsigned int batchCount) :
        m_BatchCount(batchCount)
    {
        unsigned int indices[m_BatchCount*6];
        for (int i=0; i<m_BatchCount; i++) {
            indices[i  ] = 0 + i*4;
            indices[i+1] = 1 + i*4;
            indices[i+2] = 2 + i*4;
            indices[i+3] = 0 + i*4;
            indices[i+4] = 2 + i*4;
            indices[i+5] = 3 + i*4;
        }

        Renderer renderer;
        renderer.BasicBlend();
        
        m_VertexArray =  std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, m_BatchCount * 4 * sizeof(Vertex), GL_DYNAMIC_DRAW);
        m_IndexBuffer =  std::make_unique<IndexBuffer>((unsigned int*)indices, 6);

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        layout.Push<float>(4);
        m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

        glm::mat4 proj = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(WIDTH/2, HEIGHT/2, 0.0f));
        glm::mat4 mvp = proj * view * model;
        
        m_Shader = std::make_unique<Shader>();
        m_Shader->Push(GL_VERTEX_SHADER, "assets/shaders/Batching.vert");
        m_Shader->Push(GL_FRAGMENT_SHADER, "assets/shaders/Batching.frag");
        m_Shader->Compile();
        m_Shader->Bind();
        m_Shader->SetUniformVec4("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        m_Shader->SetUniformMat4("u_MVP", mvp);
    }
    ~Batch () {}

    void ClearData() {
        m_Data.clear();
    }

    void SetData(const Primative::Circle* data) {
        for (int i=0; i<m_BatchCount; i++) {
            m_Data.push_back( (data+i)->vertexData[0] );
            m_Data.push_back( (data+i)->vertexData[1] );
            m_Data.push_back( (data+i)->vertexData[2] );
            m_Data.push_back( (data+i)->vertexData[3] );
        }
        m_VertexBuffer->SetData(m_Data.data(), m_Data.size());
    }

    void Draw() {
        Renderer renderer;
        renderer.Clear(0, 0, 0, 1);
        renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }
    
};
