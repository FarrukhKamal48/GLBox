#pragma once
#include <glbpch.h>

enum class FBTextureFormat {
    None = 0,

    // Color
    RGBA8,
    RED_INTEGER,

    // Depth/stencil
    DEPTH24STENCIL8,

    // Defaults
    Depth = DEPTH24STENCIL8
};

struct FBTextureSpec {
    FBTextureSpec() = default;
    FBTextureSpec(FBTextureFormat format)
        : TextureFormat(format) {}

    FBTextureFormat TextureFormat = FBTextureFormat::None;
    // maybe: filtering/wrap
};

struct FBAttachmentSpec {
    FBAttachmentSpec() = default;
    FBAttachmentSpec(std::initializer_list<FBTextureSpec> attachments)
        : Attachments(attachments) {}

    std::vector<FBTextureSpec> Attachments;
};

struct FBSpec {
    uint32_t Width = 1920;
    uint32_t Height = 1080;
    FBAttachmentSpec Attachments;
    uint32_t Samples = 1;
    
    bool SwapChainTarget = false;
};

class FrameBuffer {
public:
    FrameBuffer() = default;
    FrameBuffer(const FBSpec& spec);
    ~FrameBuffer();
    
    void ReConstruct();
    
    void Bind();
    void UnBind();
    
    // need to generalize this
    void Resize(uint32_t width, uint32_t height);
    int ReadPixel(uint32_t attachmentIndex, int x, int y);
    
    void ClearAttachment(uint32_t attachmentIndex, int value);
    
    uint32_t GetColorAttachment(uint32_t index = 0) const { 
        assert(index < m_ColorAttachments.size()); 
        return m_ColorAttachments[index]; 
    }
    
    const FBSpec& GetSpec() const { return m_Spec; }
private:
    uint32_t m_RendererID = 0;
    FBSpec m_Spec;
    
    std::vector<FBTextureSpec> m_ColorAttachmentSpecs;
    FBTextureSpec m_DepthAttachmentSpec = FBTextureFormat::None;
    
    std::vector<uint32_t> m_ColorAttachments;
    uint32_t m_DepthAttachment = 0;
};
