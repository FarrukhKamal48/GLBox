#include <glbpch.h>
#include <GL/glew.h>
#include "GLBox/Core/VertexBufferLayout.h"

template<typename T>
void Push(uint32_t count) {
    static_assert(false);
}
template<typename T>
void Push(uint32_t count, uint32_t divisor) {
    static_assert(false);
}

template<>
void VertexBufferLayout::Push<float>(uint32_t count) {
    m_Elements.push_back({ count, GL_FLOAT, GL_FALSE, 0 });
    m_Stride += count * VertexBufferLayoutElement::SizeOf(GL_FLOAT);
}
template<>
void VertexBufferLayout::Push<float>(uint32_t count, uint32_t divisor) {
    m_Elements.push_back({ count, GL_FLOAT, GL_FALSE, divisor });
    m_Stride += count * VertexBufferLayoutElement::SizeOf(GL_FLOAT);
}

template<>
void VertexBufferLayout::Push<uint32_t>(uint32_t count) {
    m_Elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE, 0 });
    m_Stride += count * VertexBufferLayoutElement::SizeOf(GL_UNSIGNED_INT);
}
template<>
void VertexBufferLayout::Push<uint32_t>(uint32_t count, uint32_t divisor) {
    m_Elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE, divisor });
    m_Stride += count * VertexBufferLayoutElement::SizeOf(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::Push<char>(uint32_t count) {
    m_Elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE, 0 });
    m_Stride += count * VertexBufferLayoutElement::SizeOf(GL_UNSIGNED_BYTE);
}
template<>
void VertexBufferLayout::Push<char>(uint32_t count, uint32_t divisor) {
    m_Elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE, divisor });
    m_Stride += count * VertexBufferLayoutElement::SizeOf(GL_UNSIGNED_BYTE);
}
