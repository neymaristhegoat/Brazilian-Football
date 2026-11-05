#pragma once

#include <string>
#include <memory>
#include <cstdint>

namespace bf {
namespace renderer {

enum class TextureFormat {
    RGB8,
    RGBA8,
    RGB16F,
    RGBA16F,
    Depth24Stencil8
};

enum class TextureFilter {
    Nearest,
    Linear,
    Bilinear,
    Trilinear
};

enum class TextureWrap {
    Repeat,
    MirroredRepeat,
    ClampToEdge,
    ClampToBorder
};

class Texture {
public:
    Texture();
    ~Texture();

    bool LoadFromFile(const std::string& filepath);
    bool LoadFromMemory(const void* data, int width, int height, TextureFormat format);
    
    void Bind(uint32_t slot = 0) const;
    void Unbind() const;

    void SetFilter(TextureFilter minFilter, TextureFilter magFilter);
    void SetWrap(TextureWrap wrapS, TextureWrap wrapT);

    uint32_t GetID() const { return m_TextureID; }
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    TextureFormat GetFormat() const { return m_Format; }

protected:
    uint32_t m_TextureID;
    int m_Width;
    int m_Height;
    TextureFormat m_Format;
};

class Texture2D : public Texture {
public:
    Texture2D() = default;
    ~Texture2D() = default;
};

class TextureCube : public Texture {
public:
    TextureCube() = default;
    ~TextureCube() = default;

    bool LoadFromFiles(const std::string& right, const std::string& left,
                      const std::string& top, const std::string& bottom,
                      const std::string& front, const std::string& back);
};

} // namespace renderer
} // namespace bf
