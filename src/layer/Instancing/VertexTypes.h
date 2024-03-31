#pragma once
#include "../Renderer.h"
#include "../../vendor/glm/ext/matrix_transform.hpp"
#include "../../vendor/glm/ext/matrix_clip_space.hpp"

class Pos2D {
public:
    glm::vec2 position;

    Pos2D() : position(0) { }
    ~Pos2D() { }

    static VertexBufferLayout Layout(unsigned int divisor) {
        VertexBufferLayout layout;
        layout.Push<float>(2, divisor);
        return layout;
    }
};

class Pos2D_RGBA {
    glm::vec2 position;
    glm::vec4 color;

    Pos2D_RGBA() : position(0), color(0) { }
    ~Pos2D_RGBA() { }

    static VertexBufferLayout Layout(unsigned int divisor) {
        VertexBufferLayout layout;
        layout.Push<float>(2, divisor);
        layout.Push<float>(4, divisor);
        return layout;
    }
};
