#pragma once

#include <glbpch.h>
#include "GLBox/Core/VertexBufferLayout.h"

class VertexBuffer {
private:
    uint32_t m_RendereID;
public:
    VertexBuffer(const void* data, uint32_t size);
    VertexBuffer(const void* data, uint32_t size, uint32_t drawType);
    ~VertexBuffer();

    void SetData(const void* data, uint32_t size, uint32_t offset = 0);

    void Bind() const;
    void UnBind() const;
};

class IndexBuffer {
private:
    uint32_t m_RendereID;
    uint32_t m_Count;
public:
    IndexBuffer(const uint32_t* data, uint32_t count);
    IndexBuffer() {}
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;

    inline uint32_t GetCount() const { return m_Count; }
};

class VertexArray {
private:
    uint32_t m_RendererID;    
    uint32_t m_AttribCount;
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void UnBind() const;

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};
