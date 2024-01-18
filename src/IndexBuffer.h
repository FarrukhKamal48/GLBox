#pragma once
#include <GL/glew.h>
#include <sys/types.h>

class IndexBuffer {
private:
    uint m_RendereID;
    uint m_Count;
public:
    IndexBuffer(const uint* data, uint count);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;

    inline uint GetCount() const { return m_Count; }
};
