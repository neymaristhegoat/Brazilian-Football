#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace bf {
namespace game {

class Player;
class Team;
class Ball;

enum class AIBehavior {
    Idle,
    SeekBall,
    MarkPlayer,
    SupportAttack,
    DefendGoal,
    MoveToPosition
};

class AIController {
public:
    AIController(Player* player);
    ~AIController();

    void Update(float deltaTime);

    void SetTeam(Team* team) { m_Team = team; }
    void SetBehavior(AIBehavior behavior) { m_Behavior = behavior; }
    
    void SetTargetPosition(const glm::vec3& position) { m_TargetPosition = position; }
    void SetTargetPlayer(Player* player) { m_TargetPlayer = player; }

private:
    void UpdateIdle(float deltaTime);
    void UpdateSeekBall(float deltaTime);
    void UpdateMarkPlayer(float deltaTime);
    void UpdateSupportAttack(float deltaTime);
    void UpdateDefendGoal(float deltaTime);
    void UpdateMoveToPosition(float deltaTime);

    void DecideBehavior();
    glm::vec3 CalculatePathToTarget(const glm::vec3& target);

private:
    Player* m_Player;
    Team* m_Team;
    AIBehavior m_Behavior;
    
    glm::vec3 m_TargetPosition;
    Player* m_TargetPlayer;
    
    float m_DecisionTimer;
    float m_DecisionInterval;
};

class TeamAI {
public:
    TeamAI(Team* team);
    ~TeamAI();

    void Initialize();
    void Update(float deltaTime);

    void SetFormationPositions();
    void AssignRoles();
    void UpdateTactics();

private:
    Team* m_Team;
    std::vector<std::unique_ptr<AIController>> m_Controllers;
    
    float m_TacticsUpdateTimer;
    float m_TacticsUpdateInterval;
};

} // namespace game
} // namespace bf
