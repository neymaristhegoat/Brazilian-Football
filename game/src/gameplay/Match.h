#pragma once

#include <memory>
#include <glm/glm.hpp>

namespace bf {
namespace game {

class Team;

enum class BallState {
    InPlay,
    OutOfBounds,
    GoalKick,
    CornerKick,
    ThrowIn,
    FreeKick,
    Penalty
};

class Ball {
public:
    Ball();
    ~Ball();

    void Initialize();
    void Update(float deltaTime);

    void SetPosition(const glm::vec3& position);
    const glm::vec3& GetPosition() const { return m_Position; }

    void SetVelocity(const glm::vec3& velocity);
    const glm::vec3& GetVelocity() const { return m_Velocity; }

    void ApplyForce(const glm::vec3& force);
    void ApplySpin(const glm::vec3& spin);

    void SetState(BallState state) { m_State = state; }
    BallState GetState() const { return m_State; }

    void Reset();

private:
    glm::vec3 m_Position;
    glm::vec3 m_Velocity;
    glm::vec3 m_Spin;
    BallState m_State;
    
    float m_Radius;
    float m_Mass;
    float m_Friction;
    float m_Bounciness;
};

class Match {
public:
    Match(Team* homeTeam, Team* awayTeam);
    ~Match();

    void Initialize();
    void Update(float deltaTime);
    void Render();

    Team* GetHomeTeam() { return m_HomeTeam; }
    Team* GetAwayTeam() { return m_AwayTeam; }
    Ball* GetBall() { return m_Ball.get(); }

    int GetHomeScore() const { return m_HomeScore; }
    int GetAwayScore() const { return m_AwayScore; }

    float GetMatchTime() const { return m_MatchTime; }
    float GetHalfDuration() const { return m_HalfDuration; }

    void ScoreGoal(Team* team);
    void KickOff();
    void Pause();
    void Resume();

private:
    Team* m_HomeTeam;
    Team* m_AwayTeam;
    std::unique_ptr<Ball> m_Ball;

    int m_HomeScore;
    int m_AwayScore;

    float m_MatchTime;
    float m_HalfDuration; // 45 minutes per half
    int m_CurrentHalf;
    bool m_Paused;
};

} // namespace game
} // namespace bf
