#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include "renderer/Texture.h"

namespace bf {
namespace renderer {

enum class FramebufferAttachmentFormat {
    None,
    RGBA8,
    RGBA16F,
    Depth24Stencil8,
    Depth32F
};

struct FramebufferAttachment {
    FramebufferAttachmentFormat format;
    std::shared_ptr<Texture> texture;
};

struct FramebufferSpec {
    uint32_t width = 1920;
    uint32_t height = 1080;
    uint32_t samples = 1; // MSAA samples
    std::vector<FramebufferAttachmentFormat> attachments;
    bool swapChainTarget = false;
};

class Framebuffer {
public:
    Framebuffer(const FramebufferSpec& spec);
    ~Framebuffer();

    void Bind() const;
    void Unbind() const;

    void Resize(uint32_t width, uint32_t height);
    void ClearAttachment(uint32_t attachmentIndex, int value);

    std::shared_ptr<Texture> GetColorAttachment(uint32_t index = 0) const;
    std::shared_ptr<Texture> GetDepthAttachment() const;

    const FramebufferSpec& GetSpec() const { return m_Spec; }

private:
    void Invalidate();

private:
    uint32_t m_FramebufferID;
    FramebufferSpec m_Spec;
    std::vector<FramebufferAttachment> m_ColorAttachments;
    FramebufferAttachment m_DepthAttachment;
};

} // namespace renderer
} // namespace bf
