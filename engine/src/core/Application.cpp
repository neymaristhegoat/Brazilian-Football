#include "core/Application.h"
#include "core/Window.h"
#include "core/Logger.h"
#include "renderer/Renderer.h"
#include "input/Input.h"
#include "audio/AudioSystem.h"
#include "scene/SceneManager.h"
#include "resources/ResourceManager.h"
#include <chrono>

namespace bf {
namespace core {

Application* Application::s_Instance = nullptr;

Application::Application()
    : m_Running(false)
    , m_LastFrameTime(0.0f)
{
    s_Instance = this;
}

Application::~Application() {
    Shutdown();
}

bool Application::Initialize(int argc, char* argv[]) {
    BF_LOG_INFO("Initializing Brazilian Football Engine...");

    // Create window
    m_Window = std::make_unique<Window>();
    if (!m_Window->Create("Brazilian Football", 1920, 1080)) {
        BF_LOG_ERROR("Failed to create window");
        return false;
    }

    // Initialize renderer
    m_Renderer = std::make_unique<Renderer>();
    if (!m_Renderer->Initialize(m_Window.get())) {
        BF_LOG_ERROR("Failed to initialize renderer");
        return false;
    }

    // Initialize input system
    m_Input = std::make_unique<Input>();
    m_Input->Initialize(m_Window.get());

    // Initialize audio system
    m_Audio = std::make_unique<AudioSystem>();
    if (!m_Audio->Initialize()) {
        BF_LOG_WARN("Failed to initialize audio system");
    }

    // Initialize resource manager
    m_ResourceManager = std::make_unique<ResourceManager>();
    m_ResourceManager->Initialize();

    // Initialize scene manager
    m_SceneManager = std::make_unique<SceneManager>();
    m_SceneManager->Initialize();

    BF_LOG_INFO("Engine initialization complete");
    m_Running = true;

    return true;
}

int Application::Run() {
    auto lastTime = std::chrono::high_resolution_clock::now();

    while (m_Running) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        ProcessEvents();
        
        if (m_Window->ShouldClose()) {
            m_Running = false;
            break;
        }

        Update(deltaTime.count());
        Render();
    }

    return 0;
}

void Application::Update(float deltaTime) {
    m_Input->Update();
    m_Audio->Update(deltaTime);
    m_SceneManager->Update(deltaTime);
}

void Application::Render() {
    m_Renderer->BeginFrame();
    m_SceneManager->Render(m_Renderer.get());
    m_Renderer->EndFrame();
    m_Window->SwapBuffers();
}

void Application::ProcessEvents() {
    m_Window->PollEvents();
}

void Application::Shutdown() {
    BF_LOG_INFO("Shutting down application...");
    
    if (m_SceneManager) m_SceneManager->Shutdown();
    if (m_ResourceManager) m_ResourceManager->Shutdown();
    if (m_Audio) m_Audio->Shutdown();
    if (m_Renderer) m_Renderer->Shutdown();
    if (m_Window) m_Window->Destroy();

    BF_LOG_INFO("Application shutdown complete");
}

} // namespace core
} // namespace bf
