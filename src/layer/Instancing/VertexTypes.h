#pragma once
#include "../../vendor/glm/ext/vector_float2.hpp"
#include "../../vendor/glm/ext/vector_float4.hpp"
#include "../VertexBufferLayout.h"

enum class VertexType {
    Vec2,
    Vec2_Vec4,
    Vec2_Vec2_Vec4,
};

class Vec2 {
public:
    glm::vec2 position;

    Vec2() : position(0) { }
    ~Vec2() { }

    static VertexBufferLayout Layout(unsigned int divisor) {
        VertexBufferLayout layout;
        layout.Push<float>(2, divisor);
        return layout;
    }
};

class Vec2_Vec4 {
public:
    glm::vec2 position;
    glm::vec4 color;

    Vec2_Vec4() : position(0), color(0) { }
    ~Vec2_Vec4() { }

    static VertexBufferLayout Layout(unsigned int divisor) {
        VertexBufferLayout layout;
        layout.Push<float>(2, divisor);
        layout.Push<float>(4, divisor);
        return layout;
    }
};

class Vec2_Vec2_Vec4 {
public:
    glm::vec2 position;
    glm::vec2 scale;
    glm::vec4 color;

    Vec2_Vec2_Vec4() : position(0), scale(0), color(0) { }
    ~Vec2_Vec2_Vec4() { }

    static VertexBufferLayout Layout(unsigned int divisor) {
        VertexBufferLayout layout;
        layout.Push<float>(2, divisor);
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
            case VertexType::Vec2     : return Vec2::Layout(divisor);
            case VertexType::Vec2_Vec4: return Vec2_Vec4::Layout(divisor);
            case VertexType::Vec2_Vec2_Vec4: return Vec2_Vec2_Vec4::Layout(divisor);
            default: {
                VertexBufferLayout layout;
                return layout;
            }
        }
    }
    static unsigned int SizeOfVertex(VertexType type) {
        switch (type) {
            case VertexType::Vec2     : return sizeof(Vec2);
            case VertexType::Vec2_Vec4: return sizeof(Vec2_Vec4);
            case VertexType::Vec2_Vec2_Vec4: return sizeof(Vec2_Vec2_Vec4);
            default: return 0;
        }
    }
    
};
