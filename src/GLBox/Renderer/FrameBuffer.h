#pragma once
#include <glbpch.h>

struct FrameBufferSpec {
    uint32_t Width; 
    uint32_t Height; 
    bool SwapChainTarget = false;
};

class FrameBuffer {
public:    
    FrameBuffer(const FrameBufferSpec& spec);
    ~FrameBuffer();

    void Resize(uint32_t width, uint32_t height);

    void Bind() const;
    void UnBind() const;

    const uint32_t GetColorAttachment() const { return m_ColorAttachment; }
    const FrameBufferSpec& GetSpec() const { return m_Spec; }
private:
    void ReCreate();
private:
    uint32_t m_RendererID = 0;
    uint32_t m_ColorAttachment = 0;
    uint32_t m_DepthAttachment = 0;
    FrameBufferSpec m_Spec;
};
