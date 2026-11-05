#include "renderer/RenderPipeline.h"
#include "renderer/Mesh.h"
#include "renderer/Material.h"
#include "renderer/RenderCommand.h"
#include "core/Logger.h"
#include <glm/gtc/type_ptr.hpp>

namespace bf {
namespace renderer {

RenderPipeline::RenderPipeline()
    : m_Width(0)
    , m_Height(0)
    , m_Camera(nullptr)
    , m_Lighting(nullptr)
    , m_BloomEnabled(false)
    , m_FXAAEnabled(true)
    , m_ToneMappingEnabled(true)
    , m_Exposure(1.0f)
{
}

RenderPipeline::~RenderPipeline() {
    Shutdown();
}

bool RenderPipeline::Initialize(uint32_t width, uint32_t height) {
    m_Width = width;
    m_Height = height;
    
    BF_LOG_INFO("Initializing RenderPipeline ({}x{})...", width, height);
    
    // Create geometry framebuffer (G-buffer for deferred rendering)
    FramebufferSpec geoSpec;
    geoSpec.width = width;
    geoSpec.height = height;
    geoSpec.attachments = {
        FramebufferAttachmentFormat::RGBA16F,  // Position + metallic
        FramebufferAttachmentFormat::RGBA16F,  // Normal + roughness
        FramebufferAttachmentFormat::RGBA8,     // Albedo
        FramebufferAttachmentFormat::Depth24Stencil8
    };
    m_GeometryFBO = std::make_shared<Framebuffer>(geoSpec);
    
    // Create lighting framebuffer (HDR)
    FramebufferSpec lightSpec;
    lightSpec.width = width;
    lightSpec.height = height;
    lightSpec.attachments = {
        FramebufferAttachmentFormat::RGBA16F,
        FramebufferAttachmentFormat::Depth24Stencil8
    };
    m_LightingFBO = std::make_shared<Framebuffer>(lightSpec);
    
    // Create post-process framebuffer
    FramebufferSpec postSpec;
    postSpec.width = width;
    postSpec.height = height;
    postSpec.attachments = {
        FramebufferAttachmentFormat::RGBA8
    };
    m_PostProcessFBO = std::make_shared<Framebuffer>(postSpec);
    
    // Load shaders
    m_GeometryShader = std::make_shared<Shader>();
    if (!m_GeometryShader->LoadFromFile("assets/shaders/pbr.vert", "assets/shaders/pbr.frag")) {
        BF_LOG_ERROR("Failed to load geometry shader");
        return false;
    }
    
    BF_LOG_INFO("RenderPipeline initialized successfully");
    return true;
}

void RenderPipeline::Shutdown() {
    BF_LOG_INFO("Shutting down RenderPipeline...");
    m_RenderQueue.clear();
    m_GeometryFBO.reset();
    m_LightingFBO.reset();
    m_PostProcessFBO.reset();
    m_GeometryShader.reset();
    m_LightingShader.reset();
    m_PostProcessShader.reset();
}

void RenderPipeline::BeginScene(const Camera& camera, const LightingSystem& lighting) {
    m_Camera = &camera;
    m_Lighting = &lighting;
    m_RenderQueue.clear();
}

void RenderPipeline::EndScene() {
    Render();
    m_Camera = nullptr;
    m_Lighting = nullptr;
}

void RenderPipeline::SubmitMesh(const Mesh* mesh, const Material* material, const glm::mat4& transform) {
    if (!mesh || !material) return;
    
    RenderObject obj;
    obj.mesh = mesh;
    obj.material = material;
    obj.transform = transform;
    m_RenderQueue.push_back(obj);
}

void RenderPipeline::SubmitMesh(const Mesh* mesh, const Shader* shader, const glm::mat4& transform) {
    if (!mesh || !shader) return;
    
    // For compatibility with direct shader submission
    RenderObject obj;
    obj.mesh = mesh;
    obj.material = nullptr;
    obj.transform = transform;
    m_RenderQueue.push_back(obj);
}

void RenderPipeline::Render() {
    if (!m_Camera || m_RenderQueue.empty()) {
        return;
    }
    
    GeometryPass();
    LightingPass();
    PostProcessPass();
}

void RenderPipeline::GeometryPass() {
    // Bind geometry framebuffer
    m_GeometryFBO->Bind();
    RenderCommand::Clear();
    
    // Set up camera matrices
    glm::mat4 view = m_Camera->GetViewMatrix();
    glm::mat4 projection = m_Camera->GetProjectionMatrix();
    
    // Render all objects
    for (const auto& obj : m_RenderQueue) {
        if (obj.material) {
            obj.material->Bind();
            auto shader = obj.material->GetShader();
            if (shader) {
                shader->SetMat4("u_View", glm::value_ptr(view));
                shader->SetMat4("u_Projection", glm::value_ptr(projection));
                shader->SetMat4("u_Model", glm::value_ptr(obj.transform));
                shader->SetVec3("u_ViewPos", m_Camera->GetPosition().x, 
                               m_Camera->GetPosition().y, m_Camera->GetPosition().z);
            }
        }
        
        if (obj.mesh) {
            obj.mesh->Bind();
            obj.mesh->Draw();
            obj.mesh->Unbind();
        }
    }
    
    m_GeometryFBO->Unbind();
}

void RenderPipeline::LightingPass() {
    // Bind lighting framebuffer
    m_LightingFBO->Bind();
    RenderCommand::Clear();
    
    // Use deferred lighting shader or forward lighting
    // For now, just copy geometry output to lighting buffer
    // In a full implementation, you'd apply all lights here
    
    m_LightingFBO->Unbind();
}

void RenderPipeline::PostProcessPass() {
    // Apply post-processing effects
    if (m_BloomEnabled) {
        ApplyBloom();
    }
    
    if (m_ToneMappingEnabled) {
        ApplyToneMapping();
    }
    
    if (m_FXAAEnabled) {
        ApplyFXAA();
    }
}

void RenderPipeline::ApplyBloom() {
    // Bloom implementation would extract bright areas and blur them
    BF_LOG_DEBUG("Applying bloom effect");
}

void RenderPipeline::ApplyFXAA() {
    // FXAA anti-aliasing implementation
    BF_LOG_DEBUG("Applying FXAA");
}

void RenderPipeline::ApplyToneMapping() {
    // HDR tone mapping (Reinhard, ACES, etc.)
    BF_LOG_DEBUG("Applying tone mapping");
}

void RenderPipeline::OnResize(uint32_t width, uint32_t height) {
    m_Width = width;
    m_Height = height;
    
    if (m_GeometryFBO) {
        m_GeometryFBO->Resize(width, height);
    }
    if (m_LightingFBO) {
        m_LightingFBO->Resize(width, height);
    }
    if (m_PostProcessFBO) {
        m_PostProcessFBO->Resize(width, height);
    }
}

std::shared_ptr<Texture> RenderPipeline::GetFinalTexture() const {
    if (m_PostProcessFBO) {
        return m_PostProcessFBO->GetColorAttachment(0);
    }
    if (m_LightingFBO) {
        return m_LightingFBO->GetColorAttachment(0);
    }
    return nullptr;
}

} // namespace renderer
} // namespace bf
