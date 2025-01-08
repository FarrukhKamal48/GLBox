#include <glbpch.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLBox/Core/GLlog.h"
#include "GLBox/Renderer/FrameBuffer.h"

namespace FB {

static GLenum TextureTarget(bool multisampled) {
    return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
}

static void BindTexture(bool multisampled, uint32_t ID) {
    GLCall(glBindTexture(TextureTarget(multisampled), ID));
}

static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count) {
    GLCall(glCreateTextures(TextureTarget(multisampled), count, outID));
}

static void AttachColorTexture(uint32_t ID, int samples, GLenum internalformat, GLenum format, uint32_t width, uint32_t height, int index) {
    if (samples > 1) {
        GLCall(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalformat, width, height, GL_FALSE));
    }
    else {
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    }
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(samples>1), ID, 0));
}

static void AttachDepthTexture(uint32_t ID, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height) {
    if (samples > 1) {
        GLCall(glTexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE));
    }
    else {
        GLCall(glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    }
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(samples>1), ID, 0));
}

static GLenum TextureFormatToGL(FBTextureFormat format) {
    switch (format) {
        case FBTextureFormat::RGBA8:        return GL_RGBA8;
        case FBTextureFormat::RED_INTEGER:  return GL_RED_INTEGER;
        default: break;
    }
    assert(false);
}


static bool IsDepthFormat(FBTextureFormat format) {
    switch (format) {
        case FBTextureFormat::DEPTH24STENCIL8:  return true; break;
        default: break;
    }
    return false;
}

}

FrameBuffer::FrameBuffer(const FrameBufferSpec& spec)
    : m_Spec(spec) 
{ 
    for (auto format : m_Spec.Attachments.Attachments) {
        if (!FB::IsDepthFormat(format.TextureFormat))
            m_ColorAttachmentSpecs.emplace_back(format);
        else
            m_DepthAttachmentSpec = format;
    }
    ReCreate(); 
}

FrameBuffer::~FrameBuffer() {
    GLCall(glDeleteFramebuffers(1, &m_RendererID));
    GLCall(glDeleteTextures(m_ColorAttachmentSpecs.size(), m_ColorAttachments.data()));
    GLCall(glDeleteTextures(1, &m_DepthAttachment));
    
    m_ColorAttachments.clear();
    m_DepthAttachment = 0;
}

void FrameBuffer::Resize(uint32_t width, uint32_t height) {
    m_Spec.Width = width;
    m_Spec.Height = height;
    ReCreate();
}

void FrameBuffer::Bind() const {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
    GLCall(glViewport(0, 0, m_Spec.Width, m_Spec.Height));
}
void FrameBuffer::UnBind() const {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

template<>
void FrameBuffer::ReadPixels(uint32_t attachmentIndex, uint32_t x, uint32_t y, FBTextureFormat format, int* pixeldata) {
    GLCall(glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex));
    GLCall(glReadPixels(x, y, 1, 1, FB::TextureFormatToGL(format), GL_INT, pixeldata));
}

template<>
void FrameBuffer::ClearColorAttachment(uint32_t attachmentIndex, int* value) {
    auto spec = m_ColorAttachmentSpecs[attachmentIndex];
    GLCall(glClearTexImage(m_ColorAttachments[attachmentIndex], 0,
               FB::TextureFormatToGL(spec.TextureFormat), GL_INT, &value));
}

void FrameBuffer::ReCreate() {
    if (m_RendererID) {
        GLCall(glDeleteFramebuffers(1, &m_RendererID));
        GLCall(glDeleteTextures(m_ColorAttachmentSpecs.size(), m_ColorAttachments.data()));
        GLCall(glDeleteTextures(1, &m_DepthAttachment));
    }

    GLCall(glGenFramebuffers(1, &m_RendererID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));

    bool multisampled = m_Spec.Samples > 1;
    if (m_ColorAttachmentSpecs.size()) {
        m_ColorAttachments.resize(m_ColorAttachmentSpecs.size());
        FB::CreateTextures(multisampled, m_ColorAttachments.data(), m_ColorAttachmentSpecs.size());
        
        for (size_t i = 0; i < m_ColorAttachmentSpecs.size(); i++) {
            FB::BindTexture(multisampled, m_ColorAttachments[i]);
            
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
        FB::CreateTextures(multisampled, &m_DepthAttachment, 1);
        FB::BindTexture(multisampled, m_DepthAttachment);
        
        switch (m_DepthAttachmentSpec.TextureFormat) {
            case FBTextureFormat::DEPTH24STENCIL8:
                FB::AttachDepthTexture(m_DepthAttachment, m_Spec.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Spec.Width, m_Spec.Height);
                break;
            default: break;
        }
    }

    if (m_ColorAttachmentSpecs.size() > 0) {
        assert(m_ColorAttachmentSpecs.size() < 4 && "GLBox doesn't support more than 4 color attachments");
        GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
        GLCall(glDrawBuffers(m_ColorAttachmentSpecs.size(), buffers));
    }
    else {
        GLCall(glDrawBuffer(GL_NONE));
    }
    
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE && "FrameBuffer is incomplete.");
    
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}
