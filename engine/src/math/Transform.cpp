#include "math/Transform.h"

namespace bf {
namespace math {

Transform::Transform()
    : m_Position(0.0f, 0.0f, 0.0f)
    , m_Rotation(1.0f, 0.0f, 0.0f, 0.0f)
    , m_Scale(1.0f, 1.0f, 1.0f)
{
}

void Transform::SetPosition(const glm::vec3& position) {
    m_Position = position;
}

void Transform::SetRotation(const glm::quat& rotation) {
    m_Rotation = rotation;
}

void Transform::SetScale(const glm::vec3& scale) {
    m_Scale = scale;
}

glm::mat4 Transform::GetMatrix() const {
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_Position);
    glm::mat4 rotation = glm::mat4_cast(m_Rotation);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Scale);
    return translation * rotation * scale;
}

void Transform::Translate(const glm::vec3& translation) {
    m_Position += translation;
}

void Transform::Rotate(float angle, const glm::vec3& axis) {
    m_Rotation = glm::angleAxis(angle, axis) * m_Rotation;
}

void Transform::Scale(const glm::vec3& scale) {
    m_Scale *= scale;
}

glm::vec3 Transform::GetForward() const {
    return glm::normalize(m_Rotation * glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::vec3 Transform::GetRight() const {
    return glm::normalize(m_Rotation * glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::vec3 Transform::GetUp() const {
    return glm::normalize(m_Rotation * glm::vec3(0.0f, 1.0f, 0.0f));
}

} // namespace math
} // namespace bf
