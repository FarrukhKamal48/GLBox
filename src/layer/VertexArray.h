#pragma once
#include "layer/VertexBuffer.h"
#include "layer/VertexBufferLayout.h"

class VertexArray {
private:
    unsigned int m_RendererID;    
    unsigned int m_AttribCount;
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void UnBind() const;

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};
