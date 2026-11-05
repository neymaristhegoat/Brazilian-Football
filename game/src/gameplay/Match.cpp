#include "gameplay/Match.h"
#include "gameplay/Team.h"
#include "core/Logger.h"

namespace bf {
namespace game {

// Ball Implementation
Ball::Ball()
    : m_Position(0.0f)
    , m_Velocity(0.0f)
    , m_Spin(0.0f)
    , m_State(BallState::InPlay)
    , m_Radius(0.11f) // Standard football radius in meters
    , m_Mass(0.45f)   // Standard football mass in kg
    , m_Friction(0.6f)
    , m_Bounciness(0.7f)
{
}

Ball::~Ball() {
}

void Ball::Initialize() {
    Reset();
}

void Ball::Update(float deltaTime) {
    // Apply physics
    m_Position += m_Velocity * deltaTime;
    
    // Apply friction
    m_Velocity *= (1.0f - m_Friction * deltaTime);
    
    // Ground collision
    if (m_Position.y < m_Radius) {
        m_Position.y = m_Radius;
        m_Velocity.y = -m_Velocity.y * m_Bounciness;
        
        // Stop if velocity is very low
        if (glm::length(m_Velocity) < 0.1f) {
            m_Velocity = glm::vec3(0.0f);
        }
    }
}

void Ball::SetPosition(const glm::vec3& position) {
    m_Position = position;
}

void Ball::SetVelocity(const glm::vec3& velocity) {
    m_Velocity = velocity;
}

void Ball::ApplyForce(const glm::vec3& force) {
    m_Velocity += force / m_Mass;
}

void Ball::ApplySpin(const glm::vec3& spin) {
    m_Spin = spin;
}

void Ball::Reset() {
    m_Position = glm::vec3(0.0f, m_Radius, 0.0f);
    m_Velocity = glm::vec3(0.0f);
    m_Spin = glm::vec3(0.0f);
    m_State = BallState::InPlay;
}

// Match Implementation
Match::Match(Team* homeTeam, Team* awayTeam)
    : m_HomeTeam(homeTeam)
    , m_AwayTeam(awayTeam)
    , m_HomeScore(0)
    , m_AwayScore(0)
    , m_MatchTime(0.0f)
    , m_HalfDuration(45.0f * 60.0f) // 45 minutes in seconds
    , m_CurrentHalf(1)
    , m_Paused(false)
{
    m_Ball = std::make_unique<Ball>();
}

Match::~Match() {
}

void Match::Initialize() {
    BF_LOG_INFO("Initializing match: {} vs {}", 
                m_HomeTeam->GetName(), m_AwayTeam->GetName());
    
    m_Ball->Initialize();
    m_HomeTeam->Initialize();
    m_AwayTeam->Initialize();
    
    KickOff();
}

void Match::Update(float deltaTime) {
    if (m_Paused) return;
    
    m_MatchTime += deltaTime;
    
    // Update teams
    m_HomeTeam->Update(deltaTime);
    m_AwayTeam->Update(deltaTime);
    
    // Update ball
    m_Ball->Update(deltaTime);
    
    // Check for half time
    if (m_CurrentHalf == 1 && m_MatchTime >= m_HalfDuration) {
        BF_LOG_INFO("Half time!");
        m_CurrentHalf = 2;
        m_MatchTime = 0.0f;
        KickOff();
    }
    
    // Check for full time
    if (m_CurrentHalf == 2 && m_MatchTime >= m_HalfDuration) {
        BF_LOG_INFO("Full time! Final score: {} {} - {} {}", 
                    m_HomeTeam->GetName(), m_HomeScore,
                    m_AwayTeam->GetName(), m_AwayScore);
    }
}

void Match::Render() {
    // TODO: Render pitch, players, ball, UI
}

void Match::ScoreGoal(Team* team) {
    if (team == m_HomeTeam) {
        m_HomeScore++;
        BF_LOG_INFO("GOAL! {} scores! {} - {}", 
                    m_HomeTeam->GetName(), m_HomeScore, m_AwayScore);
    } else if (team == m_AwayTeam) {
        m_AwayScore++;
        BF_LOG_INFO("GOAL! {} scores! {} - {}", 
                    m_AwayTeam->GetName(), m_HomeScore, m_AwayScore);
    }
    
    KickOff();
}

void Match::KickOff() {
    BF_LOG_INFO("Kick off!");
    m_Ball->Reset();
}

void Match::Pause() {
    m_Paused = true;
    BF_LOG_INFO("Match paused");
}

void Match::Resume() {
    m_Paused = false;
    BF_LOG_INFO("Match resumed");
}

} // namespace game
} // namespace bf
