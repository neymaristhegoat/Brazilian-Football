/**
 * Basic Demo Scene
 * Demonstrates the graphics engine with a simple 3D scene
 */

#include "demo/DemoScene.h"
#include "core/Logger.h"
#include "renderer/Mesh.h"
#include "renderer/Shader.h"
#include "math/Transform.h"
#include <glm/gtc/matrix_transform.hpp>

namespace bf {
namespace demo {

DemoScene::DemoScene()
    : m_Time(0.0f)
{
}

DemoScene::~DemoScene() {
}

bool DemoScene::Initialize() {
    BF_LOG_INFO("Initializing demo scene...");

    // Create camera
    m_Camera = std::make_unique<renderer::Camera>();
    m_Camera->SetPerspective(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    m_Camera->SetPosition(glm::vec3(0.0f, 5.0f, 15.0f));
    m_Camera->LookAt(glm::vec3(0.0f, 0.0f, 0.0f));

    // Create shader
    m_Shader = std::make_unique<renderer::Shader>();
    if (!m_Shader->LoadFromFile("assets/shaders/basic.vert", "assets/shaders/basic.frag")) {
        BF_LOG_ERROR("Failed to load shaders");
        return false;
    }

    // Create meshes
    m_CubeMesh = renderer::Mesh::CreateCube(2.0f);
    m_PlaneMesh = renderer::Mesh::CreatePlane(50.0f, 50.0f);
    m_SphereMesh = renderer::Mesh::CreateSphere(1.0f, 32, 16);

    BF_LOG_INFO("Demo scene initialized");
    return true;
}

void DemoScene::Update(float deltaTime) {
    m_Time += deltaTime;

    // Rotate camera around origin
    float radius = 15.0f;
    float camX = sin(m_Time * 0.5f) * radius;
    float camZ = cos(m_Time * 0.5f) * radius;
    m_Camera->SetPosition(glm::vec3(camX, 5.0f, camZ));
    m_Camera->LookAt(glm::vec3(0.0f, 0.0f, 0.0f));
}

void DemoScene::Render(renderer::Renderer* renderer) {
    // Setup shader uniforms
    m_Shader->Bind();
    
    glm::mat4 view = m_Camera->GetViewMatrix();
    glm::mat4 projection = m_Camera->GetProjectionMatrix();
    
    m_Shader->SetMat4("u_View", glm::value_ptr(view));
    m_Shader->SetMat4("u_Projection", glm::value_ptr(projection));
    
    // Light direction
    m_Shader->SetVec3("u_LightDirection", 0.3f, -0.7f, 0.3f);
    m_Shader->SetVec3("u_LightColor", 1.0f, 1.0f, 1.0f);
    m_Shader->SetVec3("u_ViewPos", m_Camera->GetPosition().x, 
                                   m_Camera->GetPosition().y, 
                                   m_Camera->GetPosition().z);
    
    m_Shader->SetBool("u_UseAlbedoMap", false);
    m_Shader->SetBool("u_UseNormalMap", false);

    // Render ground plane
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        
        m_Shader->SetMat4("u_Model", glm::value_ptr(model));
        m_Shader->SetVec3("u_Albedo", 0.2f, 0.6f, 0.2f); // Green ground
        
        m_PlaneMesh->Draw();
    }

    // Render rotating cube
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-5.0f, 2.0f, 0.0f));
        model = glm::rotate(model, m_Time, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, m_Time * 0.5f, glm::vec3(1.0f, 0.0f, 0.0f));
        
        m_Shader->SetMat4("u_Model", glm::value_ptr(model));
        m_Shader->SetVec3("u_Albedo", 0.8f, 0.2f, 0.2f); // Red cube
        
        m_CubeMesh->Draw();
    }

    // Render bouncing sphere
    {
        float bounceHeight = abs(sin(m_Time * 2.0f)) * 3.0f + 1.0f;
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(5.0f, bounceHeight, 0.0f));
        
        m_Shader->SetMat4("u_Model", glm::value_ptr(model));
        m_Shader->SetVec3("u_Albedo", 0.2f, 0.4f, 0.9f); // Blue sphere
        
        m_SphereMesh->Draw();
    }

    // Render multiple cubes in a grid
    for (int x = -2; x <= 2; x++) {
        for (int z = -2; z <= 2; z++) {
            if (x == 0 && z == 0) continue;
            
            float height = sin(m_Time + x + z) * 0.5f + 1.5f;
            
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(x * 3.0f, height, z * 3.0f));
            model = glm::scale(model, glm::vec3(0.5f));
            model = glm::rotate(model, m_Time + x + z, glm::vec3(0.0f, 1.0f, 0.0f));
            
            m_Shader->SetMat4("u_Model", glm::value_ptr(model));
            
            // Color varies based on position
            float r = (float)(x + 2) / 4.0f;
            float b = (float)(z + 2) / 4.0f;
            m_Shader->SetVec3("u_Albedo", r, 0.5f, b);
            
            m_CubeMesh->Draw();
        }
    }

    m_Shader->Unbind();
}

} // namespace demo
} // namespace bf
