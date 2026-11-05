#include "renderer/Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace bf {
namespace renderer {

Camera::Camera()
    : m_Type(CameraType::Perspective)
    , m_Position(0.0f, 0.0f, 0.0f)
    , m_Rotation(0.0f, 0.0f, 0.0f)
    , m_Front(0.0f, 0.0f, -1.0f)
    , m_Right(1.0f, 0.0f, 0.0f)
    , m_Up(0.0f, 1.0f, 0.0f)
    , m_WorldUp(0.0f, 1.0f, 0.0f)
    , m_FOV(45.0f)
    , m_AspectRatio(16.0f / 9.0f)
    , m_NearPlane(0.1f)
    , m_FarPlane(1000.0f)
    , m_ViewDirty(true)
    , m_ProjectionDirty(true)
{
}

void Camera::SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane) {
    m_Type = CameraType::Perspective;
    m_FOV = fov;
    m_AspectRatio = aspectRatio;
    m_NearPlane = nearPlane;
    m_FarPlane = farPlane;
    m_ProjectionDirty = true;
}

void Camera::SetOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
    m_Type = CameraType::Orthographic;
    m_OrthoLeft = left;
    m_OrthoRight = right;
    m_OrthoBottom = bottom;
    m_OrthoTop = top;
    m_NearPlane = nearPlane;
    m_FarPlane = farPlane;
    m_ProjectionDirty = true;
}

void Camera::SetPosition(const glm::vec3& position) {
    m_Position = position;
    m_ViewDirty = true;
}

void Camera::SetRotation(const glm::vec3& rotation) {
    m_Rotation = rotation;
    
    glm::vec3 front;
    front.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    front.y = sin(glm::radians(rotation.x));
    front.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    m_Front = glm::normalize(front);
    
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
    
    m_ViewDirty = true;
}

void Camera::LookAt(const glm::vec3& target, const glm::vec3& up) {
    m_Front = glm::normalize(target - m_Position);
    m_Right = glm::normalize(glm::cross(m_Front, up));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
    m_ViewDirty = true;
}

glm::mat4 Camera::GetViewMatrix() const {
    if (m_ViewDirty) {
        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
        m_ViewDirty = false;
    }
    return m_ViewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix() const {
    if (m_ProjectionDirty) {
        if (m_Type == CameraType::Perspective) {
            m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlane, m_FarPlane);
        } else {
            m_ProjectionMatrix = glm::ortho(m_OrthoLeft, m_OrthoRight, m_OrthoBottom, m_OrthoTop, m_NearPlane, m_FarPlane);
        }
        m_ProjectionDirty = false;
    }
    return m_ProjectionMatrix;
}

glm::mat4 Camera::GetViewProjectionMatrix() const {
    return GetProjectionMatrix() * GetViewMatrix();
}

glm::vec3 Camera::GetForward() const {
    return m_Front;
}

glm::vec3 Camera::GetRight() const {
    return m_Right;
}

glm::vec3 Camera::GetUp() const {
    return m_Up;
}

} // namespace renderer
} // namespace bf
