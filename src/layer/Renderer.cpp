#include "Renderer.h"
#include "GLlog.h"

void Render::Clear() {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
void Render::Clear(float r, float g, float b, float a) {
    GLCall(glClearColor(r, g, b, a));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Render::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) {
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
void Render::DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const int count) {
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr, count));
}

void Render::BasicBlend() {
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));
}
