#pragma once

#include "renderer/Camera.h"
#include "renderer/Renderer.h"
#include "renderer/Mesh.h"
#include "renderer/Shader.h"
#include <memory>

namespace bf {
namespace demo {

/**
 * Demo Scene
 * Simple scene to demonstrate graphics capabilities
 */
class DemoScene {
public:
    DemoScene();
    ~DemoScene();

    bool Initialize();
    void Update(float deltaTime);
    void Render(renderer::Renderer* renderer);

    renderer::Camera* GetCamera() { return m_Camera.get(); }

private:
    std::unique_ptr<renderer::Camera> m_Camera;
    std::unique_ptr<renderer::Shader> m_Shader;
    
    std::shared_ptr<renderer::Mesh> m_CubeMesh;
    std::shared_ptr<renderer::Mesh> m_PlaneMesh;
    std::shared_ptr<renderer::Mesh> m_SphereMesh;
    
    float m_Time;
};

} // namespace demo
} // namespace bf
