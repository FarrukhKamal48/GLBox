#pragma once
#include "../../vendor/glm/ext/matrix_transform.hpp"
#include "../../vendor/glm/ext/matrix_clip_space.hpp"
#include "../VertexBufferLayout.h"

enum class VertexType {
    Pos2D,
    Pos2D_RGBA,
};

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
public:
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

class VertexLookup {
public:
    VertexLookup() = delete;

    static VertexBufferLayout Layout(VertexType type, unsigned int divisor) {
        switch (type) {
            case VertexType::Pos2D     : return Pos2D::Layout(divisor);
            case VertexType::Pos2D_RGBA: return Pos2D_RGBA::Layout(divisor);
            default: {
                VertexBufferLayout layout;
                return layout;
            }
        }
    }
    static unsigned int SizeOfVertex(VertexType type) {
        switch (type) {
            case VertexType::Pos2D     : return sizeof(Pos2D);
            case VertexType::Pos2D_RGBA: return sizeof(Pos2D_RGBA);
            default: return 0;
        }
    }
    
};
