#pragma once
#include "GL/glew.h"
#include <vector>

struct VertexBufferLayoutElement {
    unsigned int count;
    unsigned int type;
    unsigned char normalized;
    unsigned int divisor;

    static unsigned int SizeOf(unsigned int type) {
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
    unsigned int m_Stride;
public:
    VertexBufferLayout()
        : m_Stride(0) 
    {}

    template<typename T>
    void Push(unsigned int count);
    
    template<typename T>
    void Push(unsigned int count, unsigned int divisor);

    inline const std::vector<VertexBufferLayoutElement>& GetElements() const { return m_Elements; }
    inline const unsigned int GetStride() const { return m_Stride; }
};
