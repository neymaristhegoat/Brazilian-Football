#pragma once

#include "renderer/Texture.h"
#include "renderer/Shader.h"
#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace bf {
namespace renderer {

class Material {
public:
    Material();
    Material(std::shared_ptr<Shader> shader);
    ~Material();

    void SetShader(std::shared_ptr<Shader> shader) { m_Shader = shader; }
    std::shared_ptr<Shader> GetShader() const { return m_Shader; }

    // Texture slots
    void SetTexture(const std::string& name, std::shared_ptr<Texture> texture);
    std::shared_ptr<Texture> GetTexture(const std::string& name) const;

    // Properties
    void SetFloat(const std::string& name, float value);
    void SetVec2(const std::string& name, const glm::vec2& value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetVec4(const std::string& name, const glm::vec4& value);
    void SetColor(const std::string& name, const glm::vec4& color);

    // Common PBR properties
    void SetAlbedo(const glm::vec3& albedo);
    void SetMetallic(float metallic);
    void SetRoughness(float roughness);
    void SetAmbientOcclusion(float ao);

    void Bind() const;

private:
    std::shared_ptr<Shader> m_Shader;
    std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
    std::unordered_map<std::string, float> m_Floats;
    std::unordered_map<std::string, glm::vec2> m_Vec2s;
    std::unordered_map<std::string, glm::vec3> m_Vec3s;
    std::unordered_map<std::string, glm::vec4> m_Vec4s;
};

} // namespace renderer
} // namespace bf
