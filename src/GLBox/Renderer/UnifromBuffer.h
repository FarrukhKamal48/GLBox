#pragma once
#include <glbpch.h>

class UniformBuffer {
public:
    UniformBuffer(const void* data, uint32_t size, uint32_t binding);
    ~UniformBuffer();

    void SetData(const void* data, uint32_t size, uint32_t offset = 0);

    void Bind() const;
    void UnBind() const;
private:
    uint32_t m_RendererID;
    uint32_t m_Binding;
};
