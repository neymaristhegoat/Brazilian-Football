#pragma once

#include "scene/Component.h"
#include "math/Transform.h"

namespace bf {
namespace scene {

class TransformComponent : public Component {
public:
    TransformComponent(Entity* owner);
    ~TransformComponent() override = default;

    math::Transform& GetTransform() { return m_Transform; }
    const math::Transform& GetTransform() const { return m_Transform; }

    void SetPosition(const glm::vec3& position) { m_Transform.SetPosition(position); }
    void SetRotation(const glm::quat& rotation) { m_Transform.SetRotation(rotation); }
    void SetScale(const glm::vec3& scale) { m_Transform.SetScale(scale); }

    const glm::vec3& GetPosition() const { return m_Transform.GetPosition(); }
    const glm::quat& GetRotation() const { return m_Transform.GetRotation(); }
    const glm::vec3& GetScale() const { return m_Transform.GetScale(); }

    glm::mat4 GetMatrix() const { return m_Transform.GetMatrix(); }

private:
    math::Transform m_Transform;
};

} // namespace scene
} // namespace bf
