#include <glbpch.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLBox/Renderer/FrameBuffer.h"

static const uint32_t s_MaxFramebufferSize = 8192;

namespace FB {

static GLenum TextureTarget(bool multisampled) {
    return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
}

static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count) {
    GLCall(glCreateTextures(TextureTarget(multisampled), count, outID));
}

static void BindTexture(bool multisampled, uint32_t id) {
    GLCall(glBindTexture(TextureTarget(multisampled), id));
}

static void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int index) {
    bool multisampled = samples > 1;
    if (multisampled) {
        GLCall(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE));
    }
    else {
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr));
        
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    }
    
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0));
}

static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height) {
    bool multisampled = samples > 1;
    if (multisampled) {
        GLCall(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE));
    }
    else {
        GLCall(glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height));
        
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    }

    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0));
}

static bool IsDepthFormat(FBTextureFormat format) {
    switch (format) {
        case FBTextureFormat::DEPTH24STENCIL8:  return true;
        default: break;
    }
    return false;
}

static GLenum FBTextureFormatToGL(FBTextureFormat format) {
    switch (format) {
        case FBTextureFormat::RGBA8:       return GL_RGBA8;
        case FBTextureFormat::RED_INTEGER: return GL_RED_INTEGER;
        default: break;
    }
    assert(false);
    return 0;
}

}

FrameBuffer::FrameBuffer(const FBSpec& specification)
    : m_Spec(specification)
{
    for (auto spec : m_Spec.Attachments.Attachments) {
        if (!FB::IsDepthFormat(spec.TextureFormat))
            m_ColorAttachmentSpecs.emplace_back(spec);
        else
            m_DepthAttachmentSpec = spec;
    }

    ReConstruct();
}

FrameBuffer::~FrameBuffer() {
    GLCall(glDeleteFramebuffers(1, &m_RendererID));
    GLCall(glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data()));
    GLCall(glDeleteTextures(1, &m_DepthAttachment));
}

void FrameBuffer::ReConstruct() {
    if (m_RendererID) {
        GLCall(glDeleteFramebuffers(1, &m_RendererID));
        GLCall(glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data()));
        GLCall(glDeleteTextures(1, &m_DepthAttachment));
        
        m_ColorAttachments.clear();
        m_DepthAttachment = 0;
    }

    GLCall(glCreateFramebuffers(1, &m_RendererID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));

    bool multisample = m_Spec.Samples > 1;

    // Attachments
    if (m_ColorAttachmentSpecs.size()) {
        m_ColorAttachments.resize(m_ColorAttachmentSpecs.size());
        FB::CreateTextures(multisample, m_ColorAttachments.data(), m_ColorAttachments.size());

        for (size_t i = 0; i < m_ColorAttachments.size(); i++) {
            FB::BindTexture(multisample, m_ColorAttachments[i]);
            switch (m_ColorAttachmentSpecs[i].TextureFormat) {
                case FBTextureFormat::RGBA8:
                    FB::AttachColorTexture(m_ColorAttachments[i], m_Spec.Samples, GL_RGBA8, GL_RGBA, m_Spec.Width, m_Spec.Height, i);
                    break;
                case FBTextureFormat::RED_INTEGER:
                    FB::AttachColorTexture(m_ColorAttachments[i], m_Spec.Samples, GL_R32I, GL_RED_INTEGER, m_Spec.Width, m_Spec.Height, i);
                    break;
                default: break;
            }
        }
    }

    if (m_DepthAttachmentSpec.TextureFormat != FBTextureFormat::None) {
        FB::CreateTextures(multisample, &m_DepthAttachment, 1);
        FB::BindTexture(multisample, m_DepthAttachment);
        switch (m_DepthAttachmentSpec.TextureFormat) {
            case FBTextureFormat::DEPTH24STENCIL8:
                FB::AttachDepthTexture(m_DepthAttachment, m_Spec.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Spec.Width, m_Spec.Height);
                break;
            default: break;
        }
    }

    if (m_ColorAttachments.size() > 1) {
        assert(m_ColorAttachments.size() <= 4);
        GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
        GLCall(glDrawBuffers(m_ColorAttachments.size(), buffers));
    }
    else if (m_ColorAttachments.empty()) {
        // Only depth-pass
        GLCall(glDrawBuffer(GL_NONE));
    }

    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE && "Framebuffer is incomplete!");

    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::Bind() {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
    GLCall(glViewport(0, 0, m_Spec.Width, m_Spec.Height));
}

void FrameBuffer::UnBind() {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::Resize(uint32_t width, uint32_t height) {
    if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize) {
        return;
    }
    
    m_Spec.Width = width;
    m_Spec.Height = height;
    ReConstruct();
}

int FrameBuffer::ReadPixel(uint32_t attachmentIndex, int x, int y) {
    assert(attachmentIndex < m_ColorAttachments.size());

    GLCall(glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex));
    int pixelData;
    GLCall(glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData));
    return pixelData;
}

void FrameBuffer::ClearAttachment(uint32_t attachmentIndex, int value) {
    assert(attachmentIndex < m_ColorAttachments.size());

    auto& spec = m_ColorAttachmentSpecs[attachmentIndex];
    GLCall(glClearTexImage(m_ColorAttachments[attachmentIndex], 0,
        FB::FBTextureFormatToGL(spec.TextureFormat), GL_INT, &value));
}

