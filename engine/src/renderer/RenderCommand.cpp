#include "renderer/RenderCommand.h"
#include "core/Logger.h"
#include <GL/glew.h>

namespace bf {
namespace renderer {

glm::vec4 RenderCommand::s_ClearColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

void RenderCommand::Init() {
    BF_LOG_INFO("Initializing RenderCommand...");
    
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    // Enable face culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Enable MSAA
    glEnable(GL_MULTISAMPLE);
    
    // Set default clear color
    glClearColor(s_ClearColor.r, s_ClearColor.g, s_ClearColor.b, s_ClearColor.a);
}

void RenderCommand::SetClearColor(const glm::vec4& color) {
    s_ClearColor = color;
    glClearColor(color.r, color.g, color.b, color.a);
}

void RenderCommand::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    glViewport(x, y, width, height);
}

void RenderCommand::SetLineWidth(float width) {
    glLineWidth(width);
}

void RenderCommand::SetPointSize(float size) {
    glPointSize(size);
}

void RenderCommand::EnableDepthTest(bool enable) {
    if (enable) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

void RenderCommand::EnableBlending(bool enable) {
    if (enable) {
        glEnable(GL_BLEND);
    } else {
        glDisable(GL_BLEND);
    }
}

void RenderCommand::EnableCulling(bool enable) {
    if (enable) {
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }
}

void RenderCommand::EnableWireframe(bool enable) {
    glPolygonMode(GL_FRONT_AND_BACK, enable ? GL_LINE : GL_FILL);
}

void RenderCommand::EnableMSAA(bool enable) {
    if (enable) {
        glEnable(GL_MULTISAMPLE);
    } else {
        glDisable(GL_MULTISAMPLE);
    }
}

void RenderCommand::SetBlendFunc(uint32_t srcFactor, uint32_t dstFactor) {
    glBlendFunc(srcFactor, dstFactor);
}

void RenderCommand::SetDepthFunc(uint32_t func) {
    glDepthFunc(func);
}

void RenderCommand::SetCullFace(uint32_t face) {
    glCullFace(face);
}

} // namespace renderer
} // namespace bf
