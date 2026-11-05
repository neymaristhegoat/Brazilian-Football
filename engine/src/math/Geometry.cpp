#include "math/Geometry.h"
#include <algorithm>
#include <cmath>

namespace bf {
namespace math {

// AABB Implementation
AABB::AABB()
    : m_Min(FLT_MAX), m_Max(-FLT_MAX)
{
}

AABB::AABB(const glm::vec3& min, const glm::vec3& max)
    : m_Min(min), m_Max(max)
{
}

glm::vec3 AABB::GetCenter() const {
    return (m_Min + m_Max) * 0.5f;
}

glm::vec3 AABB::GetSize() const {
    return m_Max - m_Min;
}

bool AABB::Contains(const glm::vec3& point) const {
    return point.x >= m_Min.x && point.x <= m_Max.x &&
           point.y >= m_Min.y && point.y <= m_Max.y &&
           point.z >= m_Min.z && point.z <= m_Max.z;
}

bool AABB::Intersects(const AABB& other) const {
    return m_Min.x <= other.m_Max.x && m_Max.x >= other.m_Min.x &&
           m_Min.y <= other.m_Max.y && m_Max.y >= other.m_Min.y &&
           m_Min.z <= other.m_Max.z && m_Max.z >= other.m_Min.z;
}

void AABB::Expand(const glm::vec3& point) {
    m_Min = glm::min(m_Min, point);
    m_Max = glm::max(m_Max, point);
}

void AABB::Merge(const AABB& other) {
    m_Min = glm::min(m_Min, other.m_Min);
    m_Max = glm::max(m_Max, other.m_Max);
}

// BoundingSphere Implementation
BoundingSphere::BoundingSphere()
    : m_Center(0.0f), m_Radius(0.0f)
{
}

BoundingSphere::BoundingSphere(const glm::vec3& center, float radius)
    : m_Center(center), m_Radius(radius)
{
}

bool BoundingSphere::Contains(const glm::vec3& point) const {
    return glm::distance(m_Center, point) <= m_Radius;
}

bool BoundingSphere::Intersects(const BoundingSphere& other) const {
    float distance = glm::distance(m_Center, other.m_Center);
    return distance <= (m_Radius + other.m_Radius);
}

bool BoundingSphere::Intersects(const AABB& aabb) const {
    glm::vec3 closest = glm::clamp(m_Center, aabb.GetMin(), aabb.GetMax());
    return glm::distance(m_Center, closest) <= m_Radius;
}

// Frustum Implementation
Frustum::Frustum() {
}

void Frustum::Update(const glm::mat4& viewProjection) {
    // Extract frustum planes from view-projection matrix
    for (int i = 0; i < 4; i++) {
        m_Planes[0][i] = viewProjection[i][3] + viewProjection[i][0]; // Left
        m_Planes[1][i] = viewProjection[i][3] - viewProjection[i][0]; // Right
        m_Planes[2][i] = viewProjection[i][3] + viewProjection[i][1]; // Bottom
        m_Planes[3][i] = viewProjection[i][3] - viewProjection[i][1]; // Top
        m_Planes[4][i] = viewProjection[i][3] + viewProjection[i][2]; // Near
        m_Planes[5][i] = viewProjection[i][3] - viewProjection[i][2]; // Far
    }

    // Normalize planes
    for (int i = 0; i < 6; i++) {
        float length = glm::length(glm::vec3(m_Planes[i]));
        m_Planes[i] /= length;
    }
}

bool Frustum::Contains(const glm::vec3& point) const {
    for (int i = 0; i < 6; i++) {
        if (glm::dot(glm::vec3(m_Planes[i]), point) + m_Planes[i].w < 0) {
            return false;
        }
    }
    return true;
}

bool Frustum::Contains(const BoundingSphere& sphere) const {
    for (int i = 0; i < 6; i++) {
        if (glm::dot(glm::vec3(m_Planes[i]), sphere.GetCenter()) + m_Planes[i].w < -sphere.GetRadius()) {
            return false;
        }
    }
    return true;
}

bool Frustum::Contains(const AABB& aabb) const {
    glm::vec3 center = aabb.GetCenter();
    glm::vec3 extents = aabb.GetSize() * 0.5f;

    for (int i = 0; i < 6; i++) {
        glm::vec3 normal(m_Planes[i]);
        float distance = glm::dot(normal, center) + m_Planes[i].w;
        float radius = glm::dot(extents, glm::abs(normal));

        if (distance < -radius) {
            return false;
        }
    }
    return true;
}

} // namespace math
} // namespace bf
