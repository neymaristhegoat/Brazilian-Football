#include "renderer/Lighting.h"

namespace bf {
namespace renderer {

Light::Light(LightType type)
    : m_Type(type)
    , m_Color(1.0f, 1.0f, 1.0f)
    , m_Intensity(1.0f)
    , m_CastShadows(false)
{
}

LightingSystem::LightingSystem()
    : m_AmbientColor(0.1f, 0.1f, 0.1f)
    , m_AmbientIntensity(0.5f)
{
}

LightingSystem::~LightingSystem() {
}

void LightingSystem::AddDirectionalLight(const DirectionalLight& light) {
    m_DirectionalLights.push_back(light);
}

void LightingSystem::AddPointLight(const PointLight& light) {
    m_PointLights.push_back(light);
}

void LightingSystem::AddSpotLight(const SpotLight& light) {
    m_SpotLights.push_back(light);
}

void LightingSystem::SetAmbientLight(const glm::vec3& color, float intensity) {
    m_AmbientColor = color;
    m_AmbientIntensity = intensity;
}

void LightingSystem::Clear() {
    m_DirectionalLights.clear();
    m_PointLights.clear();
    m_SpotLights.clear();
}

} // namespace renderer
} // namespace bf
