#include <GL/glew.h>
#include "Core/GLlog.h"
#include "Core/VertexArray.h"

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
    m_AttribCount += elements.size()+1;
}
