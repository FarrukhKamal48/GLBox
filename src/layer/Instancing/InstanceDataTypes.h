#pragma once
#include "../Renderer.h"
#include "../../vendor/glm/ext/matrix_transform.hpp"
#include "../../vendor/glm/ext/matrix_clip_space.hpp"

namespace Instancing {

struct Pos2D {
    glm::vec2 position;

    static VertexBufferLayout Layout() {
        VertexBufferLayout layout;
        layout.Push<float>(2);
        return layout;
    }
};

struct Pos2D_RGBA {
    glm::vec2 position;
    glm::vec4 color;

    static VertexBufferLayout Layout() {
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(4);
        return layout;
    }
};

}
