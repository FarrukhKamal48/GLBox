#include "GLlog.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const uint* data, uint count) 
    : m_Count(count)
{
    GLCall(glGenBuffers(1, &m_RendereID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendereID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &m_RendereID));
}

void IndexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendereID));
}

void IndexBuffer::UnBind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
