#pragma once
#include <memory>
#include "../layer/Renderer.h"
#include "../meshes/Quad.h"

template<typename MeshType, int MeshesPerBatch>
class Batch {
private:
    float m_VertexData[MeshesPerBatch * MeshType::VertexCount * MeshType::VertexMemeberCount];
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
public:
    Batch() {
        unsigned int indices[MeshesPerBatch * 6];
        for (int i=0; i<MeshesPerBatch; i++) {
            indices[6*i +0] = 0 + 4*i;
            indices[6*i +1] = 1 + 4*i;
            indices[6*i +2] = 2 + 4*i;
            indices[6*i +3] = 2 + 4*i;
            indices[6*i +4] = 3 + 4*i;
            indices[6*i +5] = 0 + 4*i;
        }
        
        m_VertexArray  = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, sizeof(m_VertexData));
        m_IndexBuffer  = std::make_unique<IndexBuffer>(indices, MeshesPerBatch * 6);
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        layout.Push<float>(4);
        m_VertexArray->AddBuffer(*m_VertexBuffer, layout);
    }
    ~Batch() {}

    void SetData(const MeshType* srcObjs, int objCount) {
        for (int i=0; i<MeshesPerBatch && i<objCount; i++) {
            memcpy(m_VertexData + MeshType::VertexCount * MeshType::VertexMemeberCount * i, srcObjs[i].GetVerticies(), srcObjs[i].GetSizeOfVerticies());
        }
        m_VertexBuffer->SetData(m_VertexData, sizeof(m_VertexData));
    }

    void Draw(Shader& shader) {
        Renderer::Draw(*m_VertexArray, *m_IndexBuffer, shader);
    }
};
