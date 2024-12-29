#pragma once
#include <GL/glew.h>
#include "Core/VertexBufferLayout.h"

class VertexBuffer {
private:
    unsigned int m_RendereID;
public:
    VertexBuffer(const void* data, unsigned int size);
    VertexBuffer(const void* data, unsigned int size, unsigned int drawType);
    ~VertexBuffer();

    void SetData(const void* data, unsigned int size, unsigned int offset = 0);

    void Bind() const;
    void UnBind() const;
};

class IndexBuffer {
private:
    unsigned int m_RendereID;
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    IndexBuffer() {}
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;

    inline unsigned int GetCount() const { return m_Count; }
};

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
