#include <glbpch.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLBox/Core/GLlog.h"
#include "GLBox/Renderer/UnifromBuffer.h"

UniformBuffer::UniformBuffer(const void* data, uint32_t size, uint32_t binding) : m_Binding(binding) {
    GLCall(glCreateBuffers(1, &m_RendererID));
    GLCall(glNamedBufferData(m_RendererID, size, data, GL_DYNAMIC_DRAW));
    GLCall(glBindBufferBase(GL_UNIFORM_BUFFER, m_Binding, m_RendererID));
}
UniformBuffer::~UniformBuffer() {
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void UniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset) {
    GLCall(glBindBufferBase(GL_UNIFORM_BUFFER, m_Binding, m_RendererID));
    GLCall(glNamedBufferSubData(m_RendererID, offset, size, data));
}

void UniformBuffer::Bind() const {
    glBindBufferBase(GL_UNIFORM_BUFFER, m_Binding, m_RendererID);
}
void UniformBuffer::UnBind() const {
    glBindBufferBase(GL_UNIFORM_BUFFER, m_Binding, 0);
}
