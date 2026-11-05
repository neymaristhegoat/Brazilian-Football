#include "gameplay/Player.h"
#include "core/Logger.h"

namespace bf {
namespace game {

Player::Player()
    : m_Name("Player")
    , m_Number(10)
    , m_Class(PlayerClass::Midfielder)
    , m_State(PlayerState::Idle)
    , m_Position(0.0f)
    , m_Velocity(0.0f)
    , m_LookDirection(0.0f, 0.0f, 1.0f)
    , m_HasBall(false)
    , m_CurrentStamina(100.0f)
{
}

Player::~Player() {
}

void Player::Initialize() {
    BF_LOG_DEBUG("Initializing player: {}", m_Name);
}

void Player::Update(float deltaTime) {
    // Update stamina
    if (m_State == PlayerState::Sprinting) {
        m_CurrentStamina -= 10.0f * deltaTime;
        if (m_CurrentStamina < 0.0f) {
            m_CurrentStamina = 0.0f;
            Sprint(false); // Stop sprinting
        }
    } else {
        m_CurrentStamina += 5.0f * deltaTime;
        if (m_CurrentStamina > m_Stats.stamina) {
            m_CurrentStamina = m_Stats.stamina;
        }
    }

    // Update position
    m_Position += m_Velocity * deltaTime;
}

void Player::Move(const glm::vec3& direction) {
    if (glm::length(direction) > 0.0f) {
        m_LookDirection = glm::normalize(direction);
        
        float speed = m_Stats.speed;
        if (m_State == PlayerState::Sprinting) {
            speed *= 1.5f;
        }
        
        m_Velocity = m_LookDirection * speed;
        m_State = PlayerState::Running;
    } else {
        m_Velocity = glm::vec3(0.0f);
        if (m_State == PlayerState::Running || m_State == PlayerState::Sprinting) {
            m_State = PlayerState::Idle;
        }
    }
}

void Player::Sprint(bool enable) {
    if (enable && m_CurrentStamina > 0.0f) {
        m_State = PlayerState::Sprinting;
    } else {
        if (m_State == PlayerState::Sprinting) {
            m_State = PlayerState::Running;
        }
    }
}

void Player::Jump() {
    // TODO: Implement jumping physics
}

void Player::Shoot(const glm::vec3& target) {
    if (!m_HasBall) return;
    
    BF_LOG_DEBUG("Player {} shooting", m_Name);
    m_State = PlayerState::Shooting;
    // TODO: Calculate shot power and direction
}

void Player::Pass(const glm::vec3& target) {
    if (!m_HasBall) return;
    
    BF_LOG_DEBUG("Player {} passing", m_Name);
    m_State = PlayerState::Passing;
    // TODO: Calculate pass power and direction
}

void Player::Tackle() {
    BF_LOG_DEBUG("Player {} tackling", m_Name);
    m_State = PlayerState::Tackling;
    // TODO: Implement tackle logic
}

void Player::RequestBall() {
    // AI players can request the ball
    BF_LOG_DEBUG("Player {} requesting ball", m_Name);
}

} // namespace game
} // namespace bf
