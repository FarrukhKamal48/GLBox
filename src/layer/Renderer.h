#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define WIDTH (float)1920
#define HEIGHT (float)1080

namespace Renderer {
    void Clear();
    void Clear(float r, float g, float b, float a);
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    void DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const int count);

    void BasicBlend();
}
