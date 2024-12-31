#include "GLBox/Core/GLlog.h"
#include "GLBox/Core/Buffer.h"

//##############################
//#####   VertexBuffer   #######
//##############################

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

//##############################
//######   IndexBuffer   #######
//##############################

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) 
    : m_Count(count)
{
    GLCall(glGenBuffers(1, &m_RendereID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendereID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
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

//##############################
//#####   VertexArray   ########
//##############################

VertexArray::VertexArray() : m_AttribCount(0) {
    GLCall(glGenVertexArrays(1, &m_RendererID));
}
VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind() const {
    GLCall(glBindVertexArray(m_RendererID));
}
void VertexArray::UnBind() const {
    GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    long int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i + m_AttribCount));
        GLCall(glVertexAttribPointer(i + m_AttribCount, element.count, element.type, element.normalized, 
                                     layout.GetStride(), (const void*)offset));
        offset += element.count * VertexBufferLayoutElement::SizeOf(element.type);
        GLCall(glVertexAttribDivisor(i + m_AttribCount, element.divisor));
    }
    m_AttribCount += elements.size();
}
