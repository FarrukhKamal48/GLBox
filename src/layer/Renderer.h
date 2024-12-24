#pragma once
#include "layer/VertexArray.h"
#include "layer/IndexBuffer.h"
#include "layer/Shader.h"

#define WIDTH (float)1920
#define HEIGHT (float)1080

namespace Render {
    void Clear();
    void Clear(float r, float g, float b, float a);
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    void DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const int count);

    void BasicBlend();
}
