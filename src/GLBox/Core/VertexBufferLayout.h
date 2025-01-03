#pragma once

#include <glbpch.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct VertexBufferLayoutElement {
    uint32_t count;
    uint32_t type;
    unsigned char normalized;
    uint32_t divisor;

    static uint32_t SizeOf(uint32_t type) {
        switch (type) {
           case GL_FLOAT:           return 4;
           case GL_UNSIGNED_INT:    return 4;
           case GL_UNSIGNED_BYTE:   return 1;
        }
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferLayoutElement> m_Elements;
    uint32_t m_Stride;
public:
    VertexBufferLayout()
        : m_Stride(0) 
    {}

    template<typename T>
    void Push(uint32_t count);
    
    template<typename T>
    void Push(uint32_t count, uint32_t divisor);

    inline const std::vector<VertexBufferLayoutElement>& GetElements() const { return m_Elements; }
    inline const uint32_t GetStride() const { return m_Stride; }
};
