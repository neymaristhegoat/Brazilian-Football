#pragma once

#include <string>
#include <memory>
#include <glm/glm.hpp>

namespace bf {
namespace game {

enum class PlayerClass {
    Striker,
    Midfielder,
    Defender,
    Goalkeeper
};

enum class PlayerState {
    Idle,
    Running,
    Sprinting,
    Dribbling,
    Shooting,
    Passing,
    Tackling,
    Celebrating
};

struct PlayerStats {
    float speed = 70.0f;
    float acceleration = 70.0f;
    float shooting = 70.0f;
    float passing = 70.0f;
    float dribbling = 70.0f;
    float defending = 70.0f;
    float physicality = 70.0f;
    float stamina = 100.0f;
};

class Player {
public:
    Player();
    ~Player();

    void Initialize();
    void Update(float deltaTime);

    // Movement
    void Move(const glm::vec3& direction);
    void Sprint(bool enable);
    void Jump();

    // Actions
    void Shoot(const glm::vec3& target);
    void Pass(const glm::vec3& target);
    void Tackle();
    void RequestBall();

    // State
    void SetState(PlayerState state) { m_State = state; }
    PlayerState GetState() const { return m_State; }

    void SetPosition(const glm::vec3& position) { m_Position = position; }
    const glm::vec3& GetPosition() const { return m_Position; }

    void SetVelocity(const glm::vec3& velocity) { m_Velocity = velocity; }
    const glm::vec3& GetVelocity() const { return m_Velocity; }

    // Properties
    void SetName(const std::string& name) { m_Name = name; }
    const std::string& GetName() const { return m_Name; }

    void SetNumber(int number) { m_Number = number; }
    int GetNumber() const { return m_Number; }

    void SetClass(PlayerClass playerClass) { m_Class = playerClass; }
    PlayerClass GetClass() const { return m_Class; }

    PlayerStats& GetStats() { return m_Stats; }
    const PlayerStats& GetStats() const { return m_Stats; }

    bool HasBall() const { return m_HasBall; }
    void SetHasBall(bool has) { m_HasBall = has; }

private:
    std::string m_Name;
    int m_Number;
    PlayerClass m_Class;
    PlayerState m_State;
    PlayerStats m_Stats;

    glm::vec3 m_Position;
    glm::vec3 m_Velocity;
    glm::vec3 m_LookDirection;

    bool m_HasBall;
    float m_CurrentStamina;
};

} // namespace game
} // namespace bf
