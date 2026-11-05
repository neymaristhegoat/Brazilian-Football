#include "scene/Scene.h"
#include "scene/Entity.h"
#include "core/Logger.h"

namespace bf {
namespace scene {

// Scene
Scene::Scene(const std::string& name)
    : m_Name(name)
    , m_NextEntityID(1)
{
}

Scene::~Scene() {
}

void Scene::OnLoad() {
    BF_LOG_INFO("Loading scene: {}", m_Name);
}

void Scene::OnUnload() {
    BF_LOG_INFO("Unloading scene: {}", m_Name);
}

void Scene::Update(float deltaTime) {
    for (auto& entity : m_Entities) {
        if (entity->IsActive()) {
            // TODO: Update entity components
        }
    }
}

void Scene::Render(Renderer* renderer) {
    for (auto& entity : m_Entities) {
        if (entity->IsActive()) {
            // TODO: Render entity components
        }
    }
}

Entity* Scene::CreateEntity(const std::string& name) {
    auto entity = std::make_unique<Entity>(this, m_NextEntityID++);
    entity->SetName(name);
    
    Entity* ptr = entity.get();
    m_EntityMap[ptr->GetID()] = ptr;
    m_Entities.push_back(std::move(entity));
    
    return ptr;
}

void Scene::DestroyEntity(Entity* entity) {
    // TODO: Implement entity destruction
}

Entity* Scene::FindEntityByName(const std::string& name) {
    for (auto& entity : m_Entities) {
        if (entity->GetName() == name) {
            return entity.get();
        }
    }
    return nullptr;
}

Entity* Scene::FindEntityByID(uint64_t id) {
    auto it = m_EntityMap.find(id);
    return (it != m_EntityMap.end()) ? it->second : nullptr;
}

// SceneManager
SceneManager::SceneManager()
    : m_ActiveScene(nullptr)
{
}

SceneManager::~SceneManager() {
}

void SceneManager::Initialize() {
    BF_LOG_INFO("Initializing scene manager...");
}

void SceneManager::Shutdown() {
    if (m_ActiveScene) {
        m_ActiveScene->OnUnload();
    }
    m_Scenes.clear();
}

void SceneManager::Update(float deltaTime) {
    if (m_ActiveScene) {
        m_ActiveScene->Update(deltaTime);
    }
}

void SceneManager::Render(Renderer* renderer) {
    if (m_ActiveScene) {
        m_ActiveScene->Render(renderer);
    }
}

Scene* SceneManager::CreateScene(const std::string& name) {
    auto scene = std::make_unique<Scene>(name);
    Scene* ptr = scene.get();
    m_Scenes.push_back(std::move(scene));
    return ptr;
}

void SceneManager::LoadScene(const std::string& name) {
    if (m_ActiveScene) {
        m_ActiveScene->OnUnload();
    }

    for (auto& scene : m_Scenes) {
        if (scene->GetName() == name) {
            m_ActiveScene = scene.get();
            m_ActiveScene->OnLoad();
            return;
        }
    }

    BF_LOG_WARN("Scene not found: {}", name);
}

void SceneManager::UnloadScene() {
    if (m_ActiveScene) {
        m_ActiveScene->OnUnload();
        m_ActiveScene = nullptr;
    }
}

} // namespace scene
} // namespace bf
