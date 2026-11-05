#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace bf {
namespace math {

class Transform {
public:
    Transform();
    ~Transform() = default;

    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::quat& rotation);
    void SetScale(const glm::vec3& scale);

    const glm::vec3& GetPosition() const { return m_Position; }
    const glm::quat& GetRotation() const { return m_Rotation; }
    const glm::vec3& GetScale() const { return m_Scale; }

    glm::mat4 GetMatrix() const;

    void Translate(const glm::vec3& translation);
    void Rotate(float angle, const glm::vec3& axis);
    void Scale(const glm::vec3& scale);

    glm::vec3 GetForward() const;
    glm::vec3 GetRight() const;
    glm::vec3 GetUp() const;

private:
    glm::vec3 m_Position;
    glm::quat m_Rotation;
    glm::vec3 m_Scale;
};

} // namespace math
} // namespace bf
