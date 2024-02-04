#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define WIDTH (float)1920
#define HEIGHT (float)1080

class Renderer {
public:
    void Clear() const;
    void Clear(float r, float g, float b, float a) const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

    void BasicBlend();
};
