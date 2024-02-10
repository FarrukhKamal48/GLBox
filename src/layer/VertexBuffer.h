#pragma once
#include <GL/glew.h>

class VertexBuffer {
private:
    unsigned int m_RendereID;
public:
    VertexBuffer(const void* data, unsigned int size);
    VertexBuffer(const void* data, unsigned int size, unsigned int drawType);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
};
