#include "renderer/Material.h"

namespace bf {
namespace renderer {

Material::Material()
{
}

Material::Material(std::shared_ptr<Shader> shader)
    : m_Shader(shader)
{
}

Material::~Material() {
}

void Material::SetTexture(const std::string& name, std::shared_ptr<Texture> texture) {
    m_Textures[name] = texture;
}

std::shared_ptr<Texture> Material::GetTexture(const std::string& name) const {
    auto it = m_Textures.find(name);
    return (it != m_Textures.end()) ? it->second : nullptr;
}

void Material::SetFloat(const std::string& name, float value) {
    m_Floats[name] = value;
}

void Material::SetVec2(const std::string& name, const glm::vec2& value) {
    m_Vec2s[name] = value;
}

void Material::SetVec3(const std::string& name, const glm::vec3& value) {
    m_Vec3s[name] = value;
}

void Material::SetVec4(const std::string& name, const glm::vec4& value) {
    m_Vec4s[name] = value;
}

void Material::SetColor(const std::string& name, const glm::vec4& color) {
    SetVec4(name, color);
}

void Material::SetAlbedo(const glm::vec3& albedo) {
    SetVec3("u_Albedo", albedo);
}

void Material::SetMetallic(float metallic) {
    SetFloat("u_Metallic", metallic);
}

void Material::SetRoughness(float roughness) {
    SetFloat("u_Roughness", roughness);
}

void Material::SetAmbientOcclusion(float ao) {
    SetFloat("u_AO", ao);
}

void Material::Bind() const {
    if (!m_Shader) return;

    m_Shader->Bind();

    // Bind textures
    uint32_t slot = 0;
    for (const auto& [name, texture] : m_Textures) {
        if (texture) {
            texture->Bind(slot);
            m_Shader->SetInt(name, slot);
            slot++;
        }
    }

    // Set uniforms
    for (const auto& [name, value] : m_Floats) {
        m_Shader->SetFloat(name, value);
    }
    for (const auto& [name, value] : m_Vec2s) {
        m_Shader->SetVec2(name, value.x, value.y);
    }
    for (const auto& [name, value] : m_Vec3s) {
        m_Shader->SetVec3(name, value.x, value.y, value.z);
    }
    for (const auto& [name, value] : m_Vec4s) {
        m_Shader->SetVec4(name, value.x, value.y, value.z, value.w);
    }
}

} // namespace renderer
} // namespace bf
