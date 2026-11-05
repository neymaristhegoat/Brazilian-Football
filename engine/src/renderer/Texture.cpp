#include "renderer/Texture.h"
#include "core/Logger.h"
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace bf {
namespace renderer {

static GLenum TextureFormatToGL(TextureFormat format) {
    switch (format) {
        case TextureFormat::RGB8:           return GL_RGB8;
        case TextureFormat::RGBA8:          return GL_RGBA8;
        case TextureFormat::RGB16F:         return GL_RGB16F;
        case TextureFormat::RGBA16F:        return GL_RGBA16F;
        case TextureFormat::Depth24Stencil8: return GL_DEPTH24_STENCIL8;
    }
    return GL_RGBA8;
}

static GLenum TextureFormatToDataFormat(TextureFormat format) {
    switch (format) {
        case TextureFormat::RGB8:
        case TextureFormat::RGB16F:
            return GL_RGB;
        case TextureFormat::RGBA8:
        case TextureFormat::RGBA16F:
            return GL_RGBA;
        case TextureFormat::Depth24Stencil8:
            return GL_DEPTH_STENCIL;
    }
    return GL_RGBA;
}

static GLenum TextureFilterToGL(TextureFilter filter) {
    switch (filter) {
        case TextureFilter::Nearest:  return GL_NEAREST;
        case TextureFilter::Linear:   return GL_LINEAR;
        case TextureFilter::Bilinear: return GL_LINEAR_MIPMAP_NEAREST;
        case TextureFilter::Trilinear: return GL_LINEAR_MIPMAP_LINEAR;
    }
    return GL_LINEAR;
}

static GLenum TextureWrapToGL(TextureWrap wrap) {
    switch (wrap) {
        case TextureWrap::Repeat:         return GL_REPEAT;
        case TextureWrap::MirroredRepeat: return GL_MIRRORED_REPEAT;
        case TextureWrap::ClampToEdge:    return GL_CLAMP_TO_EDGE;
        case TextureWrap::ClampToBorder:  return GL_CLAMP_TO_BORDER;
    }
    return GL_REPEAT;
}

Texture::Texture()
    : m_TextureID(0)
    , m_Width(0)
    , m_Height(0)
    , m_Format(TextureFormat::RGBA8)
{
}

Texture::~Texture() {
    if (m_TextureID) {
        glDeleteTextures(1, &m_TextureID);
    }
}

bool Texture::LoadFromFile(const std::string& filepath) {
    BF_LOG_INFO("Loading texture: {}", filepath);
    
    stbi_set_flip_vertically_on_load(true);
    
    int width, height, channels;
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
    
    if (!data) {
        BF_LOG_ERROR("Failed to load texture: {}", filepath);
        return false;
    }
    
    m_Width = width;
    m_Height = height;
    
    // Determine format based on channel count
    if (channels == 3) {
        m_Format = TextureFormat::RGB8;
    } else if (channels == 4) {
        m_Format = TextureFormat::RGBA8;
    } else {
        BF_LOG_ERROR("Unsupported texture channel count: {}", channels);
        stbi_image_free(data);
        return false;
    }
    
    // Create OpenGL texture
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    
    GLenum internalFormat = TextureFormatToGL(m_Format);
    GLenum dataFormat = TextureFormatToDataFormat(m_Format);
    
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, 
                 dataFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // Default filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    stbi_image_free(data);
    
    BF_LOG_INFO("Texture loaded successfully: {} ({}x{}, {} channels, ID: {})", 
                filepath, m_Width, m_Height, channels, m_TextureID);
    return true;
}

bool Texture::LoadFromMemory(const void* data, int width, int height, TextureFormat format) {
    m_Width = width;
    m_Height = height;
    m_Format = format;
    
    if (m_TextureID) {
        glDeleteTextures(1, &m_TextureID);
    }
    
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    
    GLenum internalFormat = TextureFormatToGL(m_Format);
    GLenum dataFormat = TextureFormatToDataFormat(m_Format);
    
    GLenum dataType = GL_UNSIGNED_BYTE;
    if (format == TextureFormat::RGB16F || format == TextureFormat::RGBA16F) {
        dataType = GL_FLOAT;
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0,
                 dataFormat, dataType, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    BF_LOG_DEBUG("Texture created from memory: {}x{} (ID: {})", m_Width, m_Height, m_TextureID);
    return true;
}

void Texture::Bind(uint32_t slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetFilter(TextureFilter minFilter, TextureFilter magFilter) {
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilterToGL(minFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilterToGL(magFilter));
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetWrap(TextureWrap wrapS, TextureWrap wrapT) {
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToGL(wrapS));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToGL(wrapT));
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool TextureCube::LoadFromFiles(const std::string& right, const std::string& left,
                                const std::string& top, const std::string& bottom,
                                const std::string& front, const std::string& back) {
    BF_LOG_INFO("Loading cubemap texture...");
    
    std::string faces[6] = { right, left, top, bottom, front, back };
    
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);
    
    stbi_set_flip_vertically_on_load(false);
    
    for (uint32_t i = 0; i < 6; i++) {
        int width, height, channels;
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
        
        if (!data) {
            BF_LOG_ERROR("Failed to load cubemap face: {}", faces[i]);
            glDeleteTextures(1, &m_TextureID);
            m_TextureID = 0;
            return false;
        }
        
        if (i == 0) {
            m_Width = width;
            m_Height = height;
            m_Format = (channels == 3) ? TextureFormat::RGB8 : TextureFormat::RGBA8;
        }
        
        GLenum format = (channels == 3) ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, 
                     width, height, 0, format, GL_UNSIGNED_BYTE, data);
        
        stbi_image_free(data);
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    
    BF_LOG_INFO("Cubemap texture loaded successfully (ID: {})", m_TextureID);
    return true;
}

} // namespace renderer
} // namespace bf
