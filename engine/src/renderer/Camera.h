#pragma once

#include "math/Transform.h"
#include <glm/glm.hpp>

namespace bf {
namespace renderer {

enum class CameraType {
    Perspective,
    Orthographic
};

class Camera {
public:
    Camera();
    ~Camera() = default;

    void SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);
    void SetOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);

    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);
    void LookAt(const glm::vec3& target, const glm::vec3& up = glm::vec3(0, 1, 0));

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;
    glm::mat4 GetViewProjectionMatrix() const;

    const glm::vec3& GetPosition() const { return m_Position; }
    glm::vec3 GetForward() const;
    glm::vec3 GetRight() const;
    glm::vec3 GetUp() const;

    float GetFOV() const { return m_FOV; }
    float GetAspectRatio() const { return m_AspectRatio; }
    float GetNearPlane() const { return m_NearPlane; }
    float GetFarPlane() const { return m_FarPlane; }

private:
    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

private:
    CameraType m_Type;
    
    // Transform
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Front;
    glm::vec3 m_Right;
    glm::vec3 m_Up;
    glm::vec3 m_WorldUp;

    // Perspective
    float m_FOV;
    float m_AspectRatio;
    float m_NearPlane;
    float m_FarPlane;

    // Orthographic
    float m_Left, m_Right, m_Bottom, m_Top;

    // Matrices
    mutable glm::mat4 m_ViewMatrix;
    mutable glm::mat4 m_ProjectionMatrix;
    mutable bool m_ViewDirty;
    mutable bool m_ProjectionDirty;
};

} // namespace renderer
} // namespace bf
