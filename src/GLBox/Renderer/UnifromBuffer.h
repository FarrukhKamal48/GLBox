#pragma once

class UniformBuffer {
public:
    UniformBuffer(const void* data, unsigned int size, unsigned int binding);
    ~UniformBuffer();

    void SetData(const void* data, unsigned int size, unsigned int offset = 0);

    void Bind() const;
    void UnBind() const;
private:
    unsigned int m_RendererID;
    unsigned int m_Binding;
};
