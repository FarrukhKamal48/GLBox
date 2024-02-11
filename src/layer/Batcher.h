#pragma once
#include <memory>
#include "../layer/Renderer.h"
#include "../layer/Texture.h"
#include "../primatives/Rect.primative.h"
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/ext/matrix_clip_space.hpp"


template<int batchSize>
class Batch {
private:
    Vertex m_VertexData[batchSize*4];
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
public:
    Batch() {
        unsigned int indices[batchSize * 6];
        for (int i=0; i<batchSize; i++) {
            indices[i+0] = 0 + 4*i;
            indices[i+1] = 1 + 4*i;
            indices[i+2] = 2 + 4*i;
            indices[i+3] = 0 + 4*i;
            indices[i+4] = 2 + 4*i;
            indices[i+5] = 3 + 4*i;
        }
        
        m_VertexArray =  std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, batchSize * 4*sizeof(Vertex));
        m_IndexBuffer =  std::make_unique<IndexBuffer>(indices, batchSize * 6);
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        layout.Push<float>(4);
        m_VertexArray->AddBuffer(*m_VertexBuffer, layout);
    }
    ~Batch() {}

    void SetData(const Primative::Rect* data) {
        for (int i=0; i<batchSize; i++) {
            m_VertexData[i+0] = (data+i)->verticies[0];
            m_VertexData[i+1] = (data+i)->verticies[1];
            m_VertexData[i+2] = (data+i)->verticies[2];
            m_VertexData[i+3] = (data+i)->verticies[3];
        }
        m_VertexBuffer->SetData(m_VertexData, sizeof(m_VertexData));
    }
};
