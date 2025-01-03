#include <glbpch.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLBox/Core/GLlog.h"
#include "GLBox/Renderer/FrameBuffer.h"

FrameBuffer::FrameBuffer(const FrameBufferSpec& spec)
    : m_Spec(spec) 
{ ReCreate(); }

FrameBuffer::~FrameBuffer() {
    GLCall(glDeleteFramebuffers(1, &m_RendererID));
    GLCall(glDeleteTextures(1, &m_ColorAttachment));
    GLCall(glDeleteRenderbuffers(1, &m_DepthAttachment));
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

void FrameBuffer::ReCreate() {
    if (m_RendererID) {
        GLCall(glDeleteFramebuffers(1, &m_RendererID));
        GLCall(glDeleteTextures(1, &m_ColorAttachment));
        GLCall(glDeleteRenderbuffers(1, &m_DepthAttachment));
    }

    GLCall(glGenFramebuffers(1, &m_RendererID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
    
    GLCall(glGenTextures(1, &m_ColorAttachment));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_ColorAttachment));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Spec.Width, m_Spec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    // have to make the binding dynamicc (aka the '0' at the end)
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0));

    GLCall(glGenRenderbuffers(1, &m_DepthAttachment));
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_DepthAttachment));
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Spec.Width, m_Spec.Height));
    GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthAttachment));

    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE && "FrameBuffer is incomplete.");
    
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}
