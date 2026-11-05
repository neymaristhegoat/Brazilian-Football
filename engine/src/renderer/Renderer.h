#pragma once

#include "renderer/Shader.h"
#include <memory>
#include <glm/glm.hpp>

namespace bf {

namespace core {
class Window;
}

namespace renderer {

enum class RenderAPI {
    None = 0,
    OpenGL,
    Vulkan,
    DirectX11,
    DirectX12
};

class Mesh;
class Camera;

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool Initialize(core::Window* window);
    void Shutdown();

    void BeginFrame();
    void EndFrame();

    void Clear(float r, float g, float b, float a = 1.0f);
    void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

    // Drawing
    void DrawMesh(const Mesh* mesh, const Shader* shader, const glm::mat4& transform);

    // State management
    void SetWireframeMode(bool enabled);
    void EnableDepthTest(bool enable);
    void EnableBlending(bool enable);
    void EnableCulling(bool enable);

    RenderAPI GetAPI() const { return m_API; }

private:
    RenderAPI m_API;
    void* m_Context;
};

} // namespace renderer
} // namespace bf
