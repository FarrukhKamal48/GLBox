#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "GLBox/Core/GLlog.h"
#include "GLBox/Renderer/Renderer.h"

Renderer::RenderData Renderer::s_RenderData;

void Renderer::Clear() {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
void Renderer::Clear(float r, float g, float b, float a) {
    GLCall(glClearColor(r, g, b, a));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::BasicBlend() {
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) {
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const int count) {
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr, count));
}

void Renderer::SetViewport(int x, int y, int width, int height) {
    GLCall(glViewport(x, y, width, height));
}

