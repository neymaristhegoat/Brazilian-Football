#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace bf {

class Window;

namespace renderer {

enum class RenderAPI {
    None = 0,
    OpenGL,
    Vulkan,
    DirectX11,
    DirectX12
};

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool Initialize(Window* window);
    void Shutdown();

    void BeginFrame();
    void EndFrame();

    void Clear(float r, float g, float b, float a = 1.0f);
    void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

    RenderAPI GetAPI() const { return m_API; }

private:
    RenderAPI m_API;
    void* m_Context;
};

} // namespace renderer
} // namespace bf
