#include "renderer/Renderer.h"
#include "core/Logger.h"
#include "core/Window.h"

namespace bf {
namespace renderer {

Renderer::Renderer()
    : m_API(RenderAPI::OpenGL)
    , m_Context(nullptr)
{
}

Renderer::~Renderer() {
    Shutdown();
}

bool Renderer::Initialize(Window* window) {
    BF_LOG_INFO("Initializing renderer (OpenGL)...");
    
    // TODO: Initialize graphics API
    
    return true;
}

void Renderer::Shutdown() {
    BF_LOG_INFO("Shutting down renderer...");
    // TODO: Cleanup graphics context
}

void Renderer::BeginFrame() {
    // TODO: Begin frame rendering
}

void Renderer::EndFrame() {
    // TODO: End frame rendering
}

void Renderer::Clear(float r, float g, float b, float a) {
    // TODO: Clear framebuffer
}

void Renderer::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    // TODO: Set viewport
}

} // namespace renderer
} // namespace bf
