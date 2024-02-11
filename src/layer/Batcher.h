#pragma once
#include <cstring>
#include <memory>
#include "../layer/Renderer.h"
#include "../primatives/Rect.primative.h"


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
            indices[6*i +0] = 0 + 4*i;
            indices[6*i +1] = 1 + 4*i;
            indices[6*i +2] = 2 + 4*i;
            indices[6*i +3] = 2 + 4*i;
            indices[6*i +4] = 3 + 4*i;
            indices[6*i +5] = 0 + 4*i;
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

    void SetData(const Primative::Rect* rects) {
        for (int i=0; i<batchSize; i++) {
            memcpy(m_VertexData + 4*i, rects[i].verticies, sizeof(rects[i].verticies));
        }
        m_VertexBuffer->SetData(m_VertexData, sizeof(m_VertexData));
    }

    void Draw(Shader& shader) {
        Renderer renderer;
        renderer.Draw(*m_VertexArray, *m_IndexBuffer, shader);
    }
};
