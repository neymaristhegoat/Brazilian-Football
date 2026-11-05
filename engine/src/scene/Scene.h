#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

namespace bf {

class Renderer;

namespace scene {

class Entity;

class Scene {
public:
    Scene(const std::string& name);
    ~Scene();

    void OnLoad();
    void OnUnload();
    void Update(float deltaTime);
    void Render(Renderer* renderer);

    Entity* CreateEntity(const std::string& name = "Entity");
    void DestroyEntity(Entity* entity);
    Entity* FindEntityByName(const std::string& name);
    Entity* FindEntityByID(uint64_t id);

    const std::string& GetName() const { return m_Name; }

private:
    std::string m_Name;
    std::vector<std::unique_ptr<Entity>> m_Entities;
    std::unordered_map<uint64_t, Entity*> m_EntityMap;
    uint64_t m_NextEntityID;
};

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    void Initialize();
    void Shutdown();
    void Update(float deltaTime);
    void Render(Renderer* renderer);

    Scene* CreateScene(const std::string& name);
    void LoadScene(const std::string& name);
    void UnloadScene();

    Scene* GetActiveScene() const { return m_ActiveScene; }

private:
    std::vector<std::unique_ptr<Scene>> m_Scenes;
    Scene* m_ActiveScene;
};

} // namespace scene
} // namespace bf
