#pragma once
#include "../../vendor/glm/glm.hpp"

namespace Vertex {

struct PosUvCol {
    glm::vec2 Position;
    glm::vec2 UV;
    glm::vec4 Color;
    static const int floatCount = 8;
};

}
