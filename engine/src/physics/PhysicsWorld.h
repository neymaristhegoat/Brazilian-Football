#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace bf {
namespace physics {

enum class CollisionShape {
    Sphere,
    Box,
    Capsule,
    Mesh
};

struct RaycastHit {
    glm::vec3 point;
    glm::vec3 normal;
    float distance;
    void* collider;
};

class Collider {
public:
    virtual ~Collider() = default;
    virtual CollisionShape GetShape() const = 0;
};

class SphereCollider : public Collider {
public:
    SphereCollider(float radius) : m_Radius(radius) {}
    CollisionShape GetShape() const override { return CollisionShape::Sphere; }
    float GetRadius() const { return m_Radius; }
private:
    float m_Radius;
};

class BoxCollider : public Collider {
public:
    BoxCollider(const glm::vec3& size) : m_Size(size) {}
    CollisionShape GetShape() const override { return CollisionShape::Box; }
    const glm::vec3& GetSize() const { return m_Size; }
private:
    glm::vec3 m_Size;
};

class CapsuleCollider : public Collider {
public:
    CapsuleCollider(float radius, float height) : m_Radius(radius), m_Height(height) {}
    CollisionShape GetShape() const override { return CollisionShape::Capsule; }
    float GetRadius() const { return m_Radius; }
    float GetHeight() const { return m_Height; }
private:
    float m_Radius;
    float m_Height;
};

class RigidBody {
public:
    RigidBody();
    ~RigidBody();

    void SetMass(float mass) { m_Mass = mass; }
    void SetVelocity(const glm::vec3& velocity) { m_Velocity = velocity; }
    void SetAngularVelocity(const glm::vec3& velocity) { m_AngularVelocity = velocity; }
    void SetGravity(bool enabled) { m_UseGravity = enabled; }
    void SetKinematic(bool kinematic) { m_IsKinematic = kinematic; }

    float GetMass() const { return m_Mass; }
    const glm::vec3& GetVelocity() const { return m_Velocity; }
    const glm::vec3& GetAngularVelocity() const { return m_AngularVelocity; }
    bool GetUseGravity() const { return m_UseGravity; }
    bool GetIsKinematic() const { return m_IsKinematic; }

    void AddForce(const glm::vec3& force);
    void AddImpulse(const glm::vec3& impulse);
    void AddTorque(const glm::vec3& torque);

private:
    float m_Mass;
    glm::vec3 m_Velocity;
    glm::vec3 m_AngularVelocity;
    bool m_UseGravity;
    bool m_IsKinematic;
};

class PhysicsWorld {
public:
    PhysicsWorld();
    ~PhysicsWorld();

    bool Initialize();
    void Shutdown();
    void Update(float deltaTime);

    void SetGravity(const glm::vec3& gravity);
    glm::vec3 GetGravity() const { return m_Gravity; }

    bool Raycast(const glm::vec3& origin, const glm::vec3& direction, float maxDistance, RaycastHit& hit);
    bool SphereCast(const glm::vec3& origin, float radius, const glm::vec3& direction, float maxDistance, RaycastHit& hit);

    void AddRigidBody(RigidBody* body);
    void RemoveRigidBody(RigidBody* body);

private:
    glm::vec3 m_Gravity;
    std::vector<RigidBody*> m_Bodies;
    void* m_PhysicsWorld; // Physics engine handle
};

} // namespace physics
} // namespace bf
