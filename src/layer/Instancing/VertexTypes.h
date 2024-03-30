#pragma once
#include "../Renderer.h"
#include "../../vendor/glm/ext/matrix_transform.hpp"
#include "../../vendor/glm/ext/matrix_clip_space.hpp"

class Pos2D {
public:
    glm::vec2 position;

    static VertexBufferLayout Layout(unsigned int divisor) {
        VertexBufferLayout layout;
        layout.Push<float>(2, divisor);
        return layout;
    }
};

class Pos2D_RGBA {
    glm::vec2 position;
    glm::vec4 color;

    static VertexBufferLayout Layout(unsigned int divisor) {
        VertexBufferLayout layout;
        layout.Push<float>(2, divisor);
        layout.Push<float>(4, divisor);
        return layout;
    }
};
