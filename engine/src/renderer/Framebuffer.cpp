#include "renderer/Framebuffer.h"
#include "core/Logger.h"
#include <GL/glew.h>

namespace bf {
namespace renderer {

static GLenum FramebufferAttachmentFormatToGL(FramebufferAttachmentFormat format) {
    switch (format) {
        case FramebufferAttachmentFormat::RGBA8:          return GL_RGBA8;
        case FramebufferAttachmentFormat::RGBA16F:        return GL_RGBA16F;
        case FramebufferAttachmentFormat::Depth24Stencil8: return GL_DEPTH24_STENCIL8;
        case FramebufferAttachmentFormat::Depth32F:       return GL_DEPTH_COMPONENT32F;
        case FramebufferAttachmentFormat::None:
        default:
            return 0;
    }
}

static bool IsDepthFormat(FramebufferAttachmentFormat format) {
    return format == FramebufferAttachmentFormat::Depth24Stencil8 ||
           format == FramebufferAttachmentFormat::Depth32F;
}

Framebuffer::Framebuffer(const FramebufferSpec& spec)
    : m_FramebufferID(0)
    , m_Spec(spec)
{
    Invalidate();
}

Framebuffer::~Framebuffer() {
    if (m_FramebufferID) {
        glDeleteFramebuffers(1, &m_FramebufferID);
        m_FramebufferID = 0;
    }
    
    // Textures will be deleted by their shared_ptr destructors
    m_ColorAttachments.clear();
    m_DepthAttachment.texture.reset();
}

void Framebuffer::Bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
    glViewport(0, 0, m_Spec.width, m_Spec.height);
}

void Framebuffer::Unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Resize(uint32_t width, uint32_t height) {
    if (width == 0 || height == 0 || width > 8192 || height > 8192) {
        BF_LOG_WARN("Invalid framebuffer dimensions: {}x{}", width, height);
        return;
    }
    
    m_Spec.width = width;
    m_Spec.height = height;
    Invalidate();
}

void Framebuffer::ClearAttachment(uint32_t attachmentIndex, int value) {
    if (attachmentIndex >= m_ColorAttachments.size()) {
        BF_LOG_WARN("Invalid attachment index: {}", attachmentIndex);
        return;
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
    
    auto& attachment = m_ColorAttachments[attachmentIndex];
    GLenum format = FramebufferAttachmentFormatToGL(attachment.format);
    
    if (format == GL_RGBA8 || format == GL_RGBA16F) {
        float clearValue[4] = { (float)value, (float)value, (float)value, (float)value };
        glClearBufferfv(GL_COLOR, attachmentIndex, clearValue);
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

std::shared_ptr<Texture> Framebuffer::GetColorAttachment(uint32_t index) const {
    if (index < m_ColorAttachments.size()) {
        return m_ColorAttachments[index].texture;
    }
    return nullptr;
}

std::shared_ptr<Texture> Framebuffer::GetDepthAttachment() const {
    return m_DepthAttachment.texture;
}

void Framebuffer::Invalidate() {
    // Delete old framebuffer if it exists
    if (m_FramebufferID) {
        glDeleteFramebuffers(1, &m_FramebufferID);
        m_ColorAttachments.clear();
        m_DepthAttachment.texture.reset();
    }
    
    BF_LOG_DEBUG("Creating framebuffer ({}x{}, {} samples)", 
                 m_Spec.width, m_Spec.height, m_Spec.samples);
    
    // Create framebuffer
    glGenFramebuffers(1, &m_FramebufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
    
    bool multisampled = m_Spec.samples > 1;
    GLenum textureTarget = multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
    
    // Process attachments
    if (!m_Spec.attachments.empty()) {
        uint32_t colorAttachmentIndex = 0;
        
        for (size_t i = 0; i < m_Spec.attachments.size(); i++) {
            auto format = m_Spec.attachments[i];
            
            if (format == FramebufferAttachmentFormat::None)
                continue;
            
            FramebufferAttachment attachment;
            attachment.format = format;
            attachment.texture = std::make_shared<Texture>();
            
            GLuint textureID;
            glGenTextures(1, &textureID);
            glBindTexture(textureTarget, textureID);
            
            GLenum internalFormat = FramebufferAttachmentFormatToGL(format);
            
            if (multisampled) {
                glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_Spec.samples,
                                       internalFormat, m_Spec.width, m_Spec.height, GL_FALSE);
            } else {
                if (IsDepthFormat(format)) {
                    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Spec.width, m_Spec.height,
                               0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                } else {
                    GLenum dataFormat = (internalFormat == GL_RGBA8 || internalFormat == GL_RGBA16F) ? GL_RGBA : GL_RGB;
                    GLenum dataType = (internalFormat == GL_RGBA16F) ? GL_FLOAT : GL_UNSIGNED_BYTE;
                    
                    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Spec.width, m_Spec.height,
                               0, dataFormat, dataType, nullptr);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                }
            }
            
            // Attach to framebuffer
            if (IsDepthFormat(format)) {
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                                      textureTarget, textureID, 0);
                m_DepthAttachment = attachment;
            } else {
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + colorAttachmentIndex,
                                      textureTarget, textureID, 0);
                m_ColorAttachments.push_back(attachment);
                colorAttachmentIndex++;
            }
        }
        
        // Set draw buffers
        if (m_ColorAttachments.size() > 1) {
            std::vector<GLenum> buffers(m_ColorAttachments.size());
            for (size_t i = 0; i < m_ColorAttachments.size(); i++) {
                buffers[i] = GL_COLOR_ATTACHMENT0 + i;
            }
            glDrawBuffers(static_cast<GLsizei>(buffers.size()), buffers.data());
        } else if (m_ColorAttachments.empty()) {
            // No color attachments (depth-only framebuffer)
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);
        }
    }
    
    // Check framebuffer completeness
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        const char* errorStr = "Unknown error";
        switch (status) {
            case GL_FRAMEBUFFER_UNDEFINED:                     errorStr = "Undefined"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:         errorStr = "Incomplete attachment"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: errorStr = "Missing attachment"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:        errorStr = "Incomplete draw buffer"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:        errorStr = "Incomplete read buffer"; break;
            case GL_FRAMEBUFFER_UNSUPPORTED:                   errorStr = "Unsupported"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:        errorStr = "Incomplete multisample"; break;
        }
        BF_LOG_ERROR("Framebuffer is incomplete: {}", errorStr);
    } else {
        BF_LOG_DEBUG("Framebuffer created successfully (ID: {}, {} color attachments)", 
                     m_FramebufferID, m_ColorAttachments.size());
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // namespace renderer
} // namespace bf
