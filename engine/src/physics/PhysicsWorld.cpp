#include "physics/PhysicsWorld.h"
#include "core/Logger.h"

namespace bf {
namespace physics {

// RigidBody
RigidBody::RigidBody()
    : m_Mass(1.0f)
    , m_Velocity(0.0f)
    , m_AngularVelocity(0.0f)
    , m_UseGravity(true)
    , m_IsKinematic(false)
{
}

RigidBody::~RigidBody() {
}

void RigidBody::AddForce(const glm::vec3& force) {
    if (!m_IsKinematic) {
        m_Velocity += force / m_Mass;
    }
}

void RigidBody::AddImpulse(const glm::vec3& impulse) {
    if (!m_IsKinematic) {
        m_Velocity += impulse / m_Mass;
    }
}

void RigidBody::AddTorque(const glm::vec3& torque) {
    if (!m_IsKinematic) {
        m_AngularVelocity += torque;
    }
}

// PhysicsWorld
PhysicsWorld::PhysicsWorld()
    : m_Gravity(0.0f, -9.81f, 0.0f)
    , m_PhysicsWorld(nullptr)
{
}

PhysicsWorld::~PhysicsWorld() {
    Shutdown();
}

bool PhysicsWorld::Initialize() {
    BF_LOG_INFO("Initializing physics world...");
    // TODO: Initialize physics engine (Bullet, PhysX, custom)
    return true;
}

void PhysicsWorld::Shutdown() {
    BF_LOG_INFO("Shutting down physics world...");
    m_Bodies.clear();
    // TODO: Cleanup physics engine
}

void PhysicsWorld::Update(float deltaTime) {
    // Apply gravity and integrate
    for (auto* body : m_Bodies) {
        if (body->GetUseGravity() && !body->GetIsKinematic()) {
            glm::vec3 velocity = body->GetVelocity();
            velocity += m_Gravity * deltaTime;
            body->SetVelocity(velocity);
        }
    }

    // TODO: Physics simulation step
}

void PhysicsWorld::SetGravity(const glm::vec3& gravity) {
    m_Gravity = gravity;
}

bool PhysicsWorld::Raycast(const glm::vec3& origin, const glm::vec3& direction, float maxDistance, RaycastHit& hit) {
    // TODO: Implement raycasting
    return false;
}

bool PhysicsWorld::SphereCast(const glm::vec3& origin, float radius, const glm::vec3& direction, float maxDistance, RaycastHit& hit) {
    // TODO: Implement sphere casting
    return false;
}

void PhysicsWorld::AddRigidBody(RigidBody* body) {
    m_Bodies.push_back(body);
}

void PhysicsWorld::RemoveRigidBody(RigidBody* body) {
    for (auto it = m_Bodies.begin(); it != m_Bodies.end(); ++it) {
        if (*it == body) {
            m_Bodies.erase(it);
            break;
        }
    }
}

} // namespace physics
} // namespace bf
