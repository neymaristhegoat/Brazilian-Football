#include "renderer/Renderer.h"
#include "renderer/Mesh.h"
#include "core/Logger.h"
#include "core/Window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

namespace bf {
namespace renderer {

static void GLAPIENTRY OpenGLMessageCallback(
    GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* message, const void* userParam)
{
    // Filter out non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    const char* severityStr = "UNKNOWN";
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:         severityStr = "HIGH"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       severityStr = "MEDIUM"; break;
        case GL_DEBUG_SEVERITY_LOW:          severityStr = "LOW"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: severityStr = "NOTIFICATION"; break;
    }

    if (severity != GL_DEBUG_SEVERITY_NOTIFICATION) {
        BF_LOG_WARN("OpenGL [{}]: {}", severityStr, message);
    }
}

Renderer::Renderer()
    : m_API(RenderAPI::OpenGL)
    , m_Context(nullptr)
{
}

Renderer::~Renderer() {
    Shutdown();
}

bool Renderer::Initialize(bf::core::Window* window) {
    BF_LOG_INFO("Initializing OpenGL renderer...");
    
    // Ensure GLFW context is current
    if (!window) {
        BF_LOG_ERROR("Window is null");
        return false;
    }
    
    // Get OpenGL version first to verify context is working
    const GLubyte* glVersion = glGetString(GL_VERSION);
    if (!glVersion) {
        BF_LOG_ERROR("No OpenGL context is current");
        return false;
    }
    BF_LOG_INFO("OpenGL Context Version: {}", (const char*)glVersion);
    
    // Initialize GLEW with experimental features for core profile
    // On Wayland, GLEW may fail to detect GLX but OpenGL still works
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        BF_LOG_WARN("GLEW initialization reported an error: {}", (const char*)glewGetErrorString(err));
        BF_LOG_INFO("Attempting to continue with native GLFW loader...");
        
        // On Wayland systems, GLEW may fail but OpenGL functions are still available
        // through GLFW. We'll check if basic OpenGL calls work.
        if (!glVersion) {
            BF_LOG_ERROR("OpenGL context is not functional");
            return false;
        }
    } else {
        BF_LOG_INFO("GLEW initialized successfully");
    }
    
    // Clear any OpenGL errors from glewInit (known issue with core profile)
    while (glGetError() != GL_NO_ERROR) {
        // Clear error queue
    }

    // Get OpenGL info
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    BF_LOG_INFO("OpenGL Vendor: {}", (const char*)vendor);
    BF_LOG_INFO("OpenGL Renderer: {}", (const char*)renderer);
    BF_LOG_INFO("OpenGL Version: {}", (const char*)version);
    BF_LOG_INFO("GLSL Version: {}", (const char*)glslVersion);

    // Enable debug output
    #ifndef NDEBUG
    if (GLEW_ARB_debug_output) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLMessageCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        BF_LOG_INFO("OpenGL debug output enabled");
    }
    #endif

    // Configure OpenGL state
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // MSAA
    glEnable(GL_MULTISAMPLE);
    
    // Set initial viewport
    SetViewport(0, 0, window->GetWidth(), window->GetHeight());

    BF_LOG_INFO("OpenGL renderer initialized successfully");
    return true;
}

void Renderer::Shutdown() {
    BF_LOG_INFO("Shutting down renderer...");
    // Cleanup will be handled by individual resource destructors
}

void Renderer::BeginFrame() {
    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::EndFrame() {
    // Frame complete
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        BF_LOG_ERROR("OpenGL error at end of frame: {}", error);
    }
}

void Renderer::Clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    glViewport(x, y, width, height);
    BF_LOG_DEBUG("Viewport set to: {}x{} at ({}, {})", width, height, x, y);
}

void Renderer::DrawMesh(const Mesh* mesh, const Shader* shader, const glm::mat4& transform) {
    if (!mesh || !shader) return;
    
    shader->Bind();
    shader->SetMat4("u_Model", glm::value_ptr(transform));
    
    mesh->Bind();
    mesh->Draw();
    mesh->Unbind();
    
    shader->Unbind();
}

void Renderer::SetWireframeMode(bool enabled) {
    glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
}

void Renderer::EnableDepthTest(bool enable) {
    if (enable) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

void Renderer::EnableBlending(bool enable) {
    if (enable) {
        glEnable(GL_BLEND);
    } else {
        glDisable(GL_BLEND);
    }
}

void Renderer::EnableCulling(bool enable) {
    if (enable) {
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }
}

} // namespace renderer
} // namespace bf
