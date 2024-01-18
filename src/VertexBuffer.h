#pragma once
#include <GL/glew.h>
#include <sys/types.h>

class VertexBuffer {
private:
    uint m_RendereID;
public:
    VertexBuffer(const void* data, uint size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
};
