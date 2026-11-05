#pragma once

#include <memory>
#include <string>
#include <chrono>

namespace bf {

class Window;

namespace core {

class Window;

} // namespace core

namespace renderer {
class Renderer;
}

namespace input {
class Input;
}

namespace audio {
class AudioSystem;
}

namespace scene {
class SceneManager;
}

namespace resources {
class ResourceManager;
}

namespace core {

/**
 * Main application class
 * Manages core systems and game loop
 */
class Application {
public:
    Application();
    ~Application();

    bool Initialize(int argc, char* argv[]);
    int Run();
    void Shutdown();

    // Accessors
    Window* GetWindow() const { return m_Window.get(); }
    renderer::Renderer* GetRenderer() const { return m_Renderer.get(); }
    input::Input* GetInput() const { return m_Input.get(); }
    audio::AudioSystem* GetAudio() const { return m_Audio.get(); }
    scene::SceneManager* GetSceneManager() const { return m_SceneManager.get(); }
    resources::ResourceManager* GetResourceManager() const { return m_ResourceManager.get(); }

    static Application& Get() { return *s_Instance; }

private:
    void Update(float deltaTime);
    void Render();
    void ProcessEvents();

private:
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<renderer::Renderer> m_Renderer;
    std::unique_ptr<input::Input> m_Input;
    std::unique_ptr<audio::AudioSystem> m_Audio;
    std::unique_ptr<scene::SceneManager> m_SceneManager;
    std::unique_ptr<resources::ResourceManager> m_ResourceManager;

    bool m_Running;
    float m_LastFrameTime;

    static Application* s_Instance;
};

} // namespace core
} // namespace bf
