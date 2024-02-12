#pragma once
#include <memory>
#include "../layer/Renderer.h"
#include "../meshes/Quad.h"

template<int BatchObjCount>
class Batch {
private:
    Vertex m_VertexData[BatchObjCount*4];
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
public:
    Batch() {
        unsigned int indices[BatchObjCount * 6];
        for (int i=0; i<BatchObjCount; i++) {
            indices[6*i +0] = 0 + 4*i;
            indices[6*i +1] = 1 + 4*i;
            indices[6*i +2] = 2 + 4*i;
            indices[6*i +3] = 2 + 4*i;
            indices[6*i +4] = 3 + 4*i;
            indices[6*i +5] = 0 + 4*i;
        }
        
        m_VertexArray =  std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, BatchObjCount * 4*sizeof(Vertex));
        m_IndexBuffer =  std::make_unique<IndexBuffer>(indices, BatchObjCount * 6);
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        layout.Push<float>(4);
        m_VertexArray->AddBuffer(*m_VertexBuffer, layout);
    }
    ~Batch() {}

    void SetData(const Mesh::Quad* srcObjs, const void* endptr) {
        for (int i=0; i<BatchObjCount; i++) {
            if (srcObjs+i > endptr) break;
            memcpy(m_VertexData + 4*i, srcObjs[i].verticies, sizeof(srcObjs[i].verticies));
        }
        m_VertexBuffer->SetData(m_VertexData, sizeof(m_VertexData));
    }

    void Draw(Shader& shader) {
        Renderer renderer;
        renderer.Draw(*m_VertexArray, *m_IndexBuffer, shader);
    }
};
