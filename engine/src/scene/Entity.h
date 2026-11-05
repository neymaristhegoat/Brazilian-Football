#pragma once

#include <string>
#include <memory>
#include <vector>

namespace bf {
namespace scene {

class Entity;
class Component;
class Scene;

/**
 * Entity Component System
 */
class Entity {
public:
    Entity(Scene* scene, uint64_t id);
    ~Entity();

    template<typename T, typename... Args>
    T* AddComponent(Args&&... args);

    template<typename T>
    T* GetComponent();

    template<typename T>
    bool HasComponent() const;

    template<typename T>
    void RemoveComponent();

    uint64_t GetID() const { return m_ID; }
    Scene* GetScene() const { return m_Scene; }

    const std::string& GetName() const { return m_Name; }
    void SetName(const std::string& name) { m_Name = name; }

    bool IsActive() const { return m_Active; }
    void SetActive(bool active) { m_Active = active; }

private:
    Scene* m_Scene;
    uint64_t m_ID;
    std::string m_Name;
    bool m_Active;
    std::vector<std::unique_ptr<Component>> m_Components;
};

class Component {
public:
    Component(Entity* owner) : m_Owner(owner), m_Enabled(true) {}
    virtual ~Component() = default;

    virtual void OnStart() {}
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnDestroy() {}

    Entity* GetOwner() const { return m_Owner; }
    
    bool IsEnabled() const { return m_Enabled; }
    void SetEnabled(bool enabled) { m_Enabled = enabled; }

protected:
    Entity* m_Owner;
    bool m_Enabled;
};

} // namespace scene
} // namespace bf
