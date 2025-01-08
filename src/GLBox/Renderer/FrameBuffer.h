#pragma once
#include <glbpch.h>

enum class FBTextureFormat {
    None = 0,
    RGBA8,
    RED_INTEGER,
    DEPTH24STENCIL8,
    Depth = DEPTH24STENCIL8
};

struct FBTextureSpec {
    FBTextureSpec() = default;
    FBTextureSpec(FBTextureFormat format) : TextureFormat(format) {}
    
    FBTextureFormat TextureFormat = FBTextureFormat::None; 
};

struct FBAttachments {
    FBAttachments() = default;
    FBAttachments(std::initializer_list<FBTextureSpec> list) : Attachments(list) {}
    
    std::vector<FBTextureSpec> Attachments;
};

struct FrameBufferSpec {
    uint32_t Width; 
    uint32_t Height; 
    FBAttachments Attachments;
    bool SwapChainTarget = false;
    uint32_t Samples = 1;
};

class FrameBuffer {
public:    
    FrameBuffer() = default;
    FrameBuffer(const FrameBufferSpec& spec);
    ~FrameBuffer();

    void Resize(uint32_t width, uint32_t height);

    void Bind() const;
    void UnBind() const;

    void ReadPixels(uint32_t colorAttachment, uint32_t x, uint32_t y, FBTextureFormat format, void* pixeldata);
    const uint32_t GetColorAttachment(uint32_t index = 0) const { return m_ColorAttachments[index]; }
    const FrameBufferSpec& GetSpec() const { return m_Spec; }
private:
    void ReCreate();
private:
    uint32_t m_RendererID = 0;
    FrameBufferSpec m_Spec;

    std::vector<FBTextureSpec> m_ColorAttachmentSpecs;
    FBTextureSpec m_DepthAttachmentSpec;
    
    std::vector<uint32_t> m_ColorAttachments;
    uint32_t m_DepthAttachment = 0;
};
