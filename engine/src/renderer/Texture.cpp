#include "renderer/Texture.h"
#include "core/Logger.h"

namespace bf {
namespace renderer {

Texture::Texture()
    : m_TextureID(0)
    , m_Width(0)
    , m_Height(0)
    , m_Format(TextureFormat::RGBA8)
{
}

Texture::~Texture() {
    // TODO: Delete texture
}

bool Texture::LoadFromFile(const std::string& filepath) {
    BF_LOG_INFO("Loading texture: {}", filepath);
    // TODO: Load image file (stb_image)
    return true;
}

bool Texture::LoadFromMemory(const void* data, int width, int height, TextureFormat format) {
    m_Width = width;
    m_Height = height;
    m_Format = format;
    // TODO: Upload to GPU
    return true;
}

void Texture::Bind(uint32_t slot) const {
    // TODO: Bind texture to slot
}

void Texture::Unbind() const {
    // TODO: Unbind texture
}

void Texture::SetFilter(TextureFilter minFilter, TextureFilter magFilter) {
    // TODO: Set texture filtering
}

void Texture::SetWrap(TextureWrap wrapS, TextureWrap wrapT) {
    // TODO: Set texture wrapping
}

bool TextureCube::LoadFromFiles(const std::string& right, const std::string& left,
                                const std::string& top, const std::string& bottom,
                                const std::string& front, const std::string& back) {
    BF_LOG_INFO("Loading cubemap texture...");
    // TODO: Load 6 faces
    return true;
}

} // namespace renderer
} // namespace bf
