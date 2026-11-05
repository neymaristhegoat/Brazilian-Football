#include "renderer/Framebuffer.h"
#include "core/Logger.h"

namespace bf {
namespace renderer {

Framebuffer::Framebuffer(const FramebufferSpec& spec)
    : m_FramebufferID(0)
    , m_Spec(spec)
{
    Invalidate();
}

Framebuffer::~Framebuffer() {
    // TODO: Delete framebuffer
}

void Framebuffer::Bind() const {
    // TODO: Bind framebuffer
}

void Framebuffer::Unbind() const {
    // TODO: Unbind framebuffer
}

void Framebuffer::Resize(uint32_t width, uint32_t height) {
    m_Spec.width = width;
    m_Spec.height = height;
    Invalidate();
}

void Framebuffer::ClearAttachment(uint32_t attachmentIndex, int value) {
    // TODO: Clear specific attachment
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
    BF_LOG_DEBUG("Creating framebuffer ({}x{})", m_Spec.width, m_Spec.height);
    // TODO: Create OpenGL framebuffer with attachments
}

} // namespace renderer
} // namespace bf
