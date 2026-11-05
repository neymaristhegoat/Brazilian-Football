#pragma once

#include <glm/glm.hpp>

namespace bf {
namespace math {

class AABB {
public:
    AABB();
    AABB(const glm::vec3& min, const glm::vec3& max);

    void SetMin(const glm::vec3& min) { m_Min = min; }
    void SetMax(const glm::vec3& max) { m_Max = max; }

    const glm::vec3& GetMin() const { return m_Min; }
    const glm::vec3& GetMax() const { return m_Max; }

    glm::vec3 GetCenter() const;
    glm::vec3 GetSize() const;

    bool Contains(const glm::vec3& point) const;
    bool Intersects(const AABB& other) const;

    void Expand(const glm::vec3& point);
    void Merge(const AABB& other);

private:
    glm::vec3 m_Min;
    glm::vec3 m_Max;
};

class BoundingSphere {
public:
    BoundingSphere();
    BoundingSphere(const glm::vec3& center, float radius);

    void SetCenter(const glm::vec3& center) { m_Center = center; }
    void SetRadius(float radius) { m_Radius = radius; }

    const glm::vec3& GetCenter() const { return m_Center; }
    float GetRadius() const { return m_Radius; }

    bool Contains(const glm::vec3& point) const;
    bool Intersects(const BoundingSphere& other) const;
    bool Intersects(const AABB& aabb) const;

private:
    glm::vec3 m_Center;
    float m_Radius;
};

class Frustum {
public:
    Frustum();

    void Update(const glm::mat4& viewProjection);

    bool Contains(const glm::vec3& point) const;
    bool Contains(const BoundingSphere& sphere) const;
    bool Contains(const AABB& aabb) const;

private:
    glm::vec4 m_Planes[6]; // Left, Right, Bottom, Top, Near, Far
};

} // namespace math
} // namespace bf
