#pragma once
#include <GL/glew.h>

class IndexBuffer {
private:
    unsigned int m_RendereID;
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    IndexBuffer() {}
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;

    inline unsigned int GetCount() const { return m_Count; }
};
