#pragma once
#include "../../vendor/glm/ext/vector_float2.hpp"
#include "../../vendor/glm/ext/vector_float4.hpp"
#include "../VertexBufferLayout.h"

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

// ###################################################################################################
// ##############################  VertexLookup  #####################################################
// ###################################################################################################

template<typename VertexT> class VertexLookup {};

template<>
class VertexLookup<Vec2> {
public:
    VertexLookup() = delete;

    static VertexBufferLayout Layout(unsigned int divisor) {
        return Vec2::Layout(divisor);
    }
    static unsigned int SizeOfVertex() {
        return sizeof(Vec2);
    }
};

template<>
class VertexLookup<Vec2_Vec4> {
public:
    VertexLookup() = delete;

    static VertexBufferLayout Layout(unsigned int divisor) {
        return Vec2_Vec4::Layout(divisor);
    }
    static unsigned int SizeOfVertex() {
        return sizeof(Vec2_Vec4);
    }
};

template<>
class VertexLookup<Vec2_Vec2_Vec4> {
public:
    VertexLookup() = delete;
    
    static VertexBufferLayout Layout(unsigned int divisor) {
        return Vec2_Vec2_Vec4::Layout(divisor);
    }
    static unsigned int SizeOfVertex() {
        return sizeof(Vec2_Vec2_Vec4);
    }
    
};
