#pragma once
#include "Core/VertexArray.h"
#include "Core/IndexBuffer.h"
#include "Core/Shader.h"


namespace Render {
    void Clear();
    void Clear(float r, float g, float b, float a);
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    void DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const int count);

    void BasicBlend();
}
