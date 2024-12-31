#pragma once

#include <glbpch.h>

#include "GLBox/Renderer/RenderCommands.h"
#include "GLBox/Renderer/Batching/Quad.h"

namespace Batching {

template<class MeshType, int MeshesPerBatch> class Batch { };

template <int MeshesPerBatch> 
class Batch<Quad, MeshesPerBatch> {
private:
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
        m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, MeshesPerBatch * Quad::GetSizeOfVerticies());
        m_IndexBuffer  = std::make_unique<IndexBuffer>(indices, MeshesPerBatch * 6);
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        layout.Push<float>(4);
        m_VertexArray->AddBuffer(*m_VertexBuffer, layout);
    }
    ~Batch() {}

    void SetData(const Quad* srcObjs, int objCount) {
        unsigned int offset = 0;
        for (int i=0; i<MeshesPerBatch && i<objCount; i++) {
            m_VertexBuffer->SetData(srcObjs[i].GetVerticies(), Quad::GetSizeOfVerticies(), offset);
            offset += srcObjs[i].GetSizeOfVerticies();
        }
    }

    void Draw(Shader& shader) {
        Render::Draw(*m_VertexArray, *m_IndexBuffer, shader);
    }
};
};
