#pragma once

#include <glm/glm.hpp>
#include <string>
#include <memory>

namespace bf {
namespace renderer {

struct DirectionalLight {
    glm::vec3 direction;
    glm::vec3 color;
    float intensity;
};

struct PointLight {
    glm::vec3 position;
    glm::vec3 color;
    float intensity;
    float radius;
    
    // Attenuation
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 color;
    float intensity;
    float innerCutoff;
    float outerCutoff;
};

enum class LightType {
    Directional,
    Point,
    Spot
};

class Light {
public:
    Light(LightType type);
    ~Light() = default;

    LightType GetType() const { return m_Type; }

    void SetColor(const glm::vec3& color) { m_Color = color; }
    void SetIntensity(float intensity) { m_Intensity = intensity; }

    const glm::vec3& GetColor() const { return m_Color; }
    float GetIntensity() const { return m_Intensity; }

    void SetCastShadows(bool cast) { m_CastShadows = cast; }
    bool CastShadows() const { return m_CastShadows; }

protected:
    LightType m_Type;
    glm::vec3 m_Color;
    float m_Intensity;
    bool m_CastShadows;
};

class LightingSystem {
public:
    LightingSystem();
    ~LightingSystem();

    void AddDirectionalLight(const DirectionalLight& light);
    void AddPointLight(const PointLight& light);
    void AddSpotLight(const SpotLight& light);

    const std::vector<DirectionalLight>& GetDirectionalLights() const { return m_DirectionalLights; }
    const std::vector<PointLight>& GetPointLights() const { return m_PointLights; }
    const std::vector<SpotLight>& GetSpotLights() const { return m_SpotLights; }

    void SetAmbientLight(const glm::vec3& color, float intensity);
    glm::vec3 GetAmbientColor() const { return m_AmbientColor; }
    float GetAmbientIntensity() const { return m_AmbientIntensity; }

    void Clear();

private:
    std::vector<DirectionalLight> m_DirectionalLights;
    std::vector<PointLight> m_PointLights;
    std::vector<SpotLight> m_SpotLights;

    glm::vec3 m_AmbientColor;
    float m_AmbientIntensity;
};

} // namespace renderer
} // namespace bf
