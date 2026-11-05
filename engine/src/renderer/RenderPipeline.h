#pragma once

#include "renderer/Renderer.h"
#include "renderer/Camera.h"
#include "renderer/Lighting.h"
#include "renderer/Framebuffer.h"
#include "renderer/Shader.h"
#include <memory>
#include <vector>

namespace bf {
namespace renderer {

class Mesh;
class Material;

struct RenderObject {
    const Mesh* mesh;
    const Material* material;
    glm::mat4 transform;
};

enum class RenderPass {
    Geometry,
    Lighting,
    Transparent,
    PostProcess
};

class RenderPipeline {
public:
    RenderPipeline();
    ~RenderPipeline();

    bool Initialize(uint32_t width, uint32_t height);
    void Shutdown();

    void BeginScene(const Camera& camera, const LightingSystem& lighting);
    void EndScene();

    void SubmitMesh(const Mesh* mesh, const Material* material, const glm::mat4& transform);
    void SubmitMesh(const Mesh* mesh, const Shader* shader, const glm::mat4& transform);
    
    void Render();
    
    void OnResize(uint32_t width, uint32_t height);
    
    // Post-processing effects
    void SetBloomEnabled(bool enabled) { m_BloomEnabled = enabled; }
    void SetFXAAEnabled(bool enabled) { m_FXAAEnabled = enabled; }
    void SetToneMappingEnabled(bool enabled) { m_ToneMappingEnabled = enabled; }
    void SetExposure(float exposure) { m_Exposure = exposure; }
    
    std::shared_ptr<Texture> GetFinalTexture() const;

private:
    void GeometryPass();
    void LightingPass();
    void PostProcessPass();
    
    void ApplyBloom();
    void ApplyFXAA();
    void ApplyToneMapping();

private:
    uint32_t m_Width;
    uint32_t m_Height;
    
    // Scene data
    const Camera* m_Camera;
    const LightingSystem* m_Lighting;
    std::vector<RenderObject> m_RenderQueue;
    
    // Framebuffers
    std::shared_ptr<Framebuffer> m_GeometryFBO;
    std::shared_ptr<Framebuffer> m_LightingFBO;
    std::shared_ptr<Framebuffer> m_PostProcessFBO;
    
    // Shaders
    std::shared_ptr<Shader> m_GeometryShader;
    std::shared_ptr<Shader> m_LightingShader;
    std::shared_ptr<Shader> m_PostProcessShader;
    
    // Post-processing settings
    bool m_BloomEnabled;
    bool m_FXAAEnabled;
    bool m_ToneMappingEnabled;
    float m_Exposure;
};

} // namespace renderer
} // namespace bf
