#pragma once

#include <memory>
#include <string>

namespace bf {
namespace core {

class Window;
class Renderer;
class Input;
class AudioSystem;
class SceneManager;
class ResourceManager;

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
    Renderer* GetRenderer() const { return m_Renderer.get(); }
    Input* GetInput() const { return m_Input.get(); }
    AudioSystem* GetAudio() const { return m_Audio.get(); }
    SceneManager* GetSceneManager() const { return m_SceneManager.get(); }
    ResourceManager* GetResourceManager() const { return m_ResourceManager.get(); }

    static Application& Get() { return *s_Instance; }

private:
    void Update(float deltaTime);
    void Render();
    void ProcessEvents();

private:
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<Renderer> m_Renderer;
    std::unique_ptr<Input> m_Input;
    std::unique_ptr<AudioSystem> m_Audio;
    std::unique_ptr<SceneManager> m_SceneManager;
    std::unique_ptr<ResourceManager> m_ResourceManager;

    bool m_Running;
    float m_LastFrameTime;

    static Application* s_Instance;
};

} // namespace core
} // namespace bf
