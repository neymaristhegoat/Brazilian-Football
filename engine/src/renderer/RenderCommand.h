#pragma once

#include <glm/glm.hpp>
#include <cstdint>

namespace bf {
namespace renderer {

class RenderCommand {
public:
    static void Init();
    static void SetClearColor(const glm::vec4& color);
    static void Clear();
    static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    
    static void SetLineWidth(float width);
    static void SetPointSize(float size);
    
    static void EnableDepthTest(bool enable);
    static void EnableBlending(bool enable);
    static void EnableCulling(bool enable);
    static void EnableWireframe(bool enable);
    static void EnableMSAA(bool enable);
    
    static void SetBlendFunc(uint32_t srcFactor, uint32_t dstFactor);
    static void SetDepthFunc(uint32_t func);
    static void SetCullFace(uint32_t face);
    
private:
    static glm::vec4 s_ClearColor;
};

} // namespace renderer
} // namespace bf
