#include "Core/GLlog.h"
#include "Core/VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) 
{
    GLCall(glGenBuffers(1, &m_RendereID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendereID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int drawType) 
{
    GLCall(glGenBuffers(1, &m_RendereID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendereID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, drawType));
}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &m_RendereID));
}

void VertexBuffer::SetData(const void* data, unsigned int size, unsigned int offset) {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendereID));
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
}

void VertexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendereID));
}

void VertexBuffer::UnBind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
