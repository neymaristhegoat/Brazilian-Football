#pragma once

#include <string>
#include <vector>
#include <memory>

namespace bf {
namespace game {

enum class MissionType {
    Match,
    Training,
    Cutscene,
    Exploration
};

enum class MissionStatus {
    Locked,
    Available,
    InProgress,
    Completed,
    Failed
};

struct StoryMission {
    std::string id;
    std::string name;
    std::string description;
    MissionType type;
    MissionStatus status;
    
    // Requirements
    std::vector<std::string> requiredMissions;
    
    // Rewards
    int experienceReward;
    int moneyReward;
};

class StoryManager {
public:
    StoryManager();
    ~StoryManager();

    bool Initialize();
    void Shutdown();
    void Update(float deltaTime);

    // Mission management
    void StartMission(const std::string& missionID);
    void CompleteMission(const std::string& missionID);
    void FailMission(const std::string& missionID);

    StoryMission* GetMission(const std::string& missionID);
    std::vector<StoryMission*> GetAvailableMissions();
    StoryMission* GetCurrentMission() { return m_CurrentMission; }

    // Player progress
    int GetPlayerLevel() const { return m_PlayerLevel; }
    int GetPlayerExperience() const { return m_PlayerExperience; }
    int GetPlayerMoney() const { return m_PlayerMoney; }

    void AddExperience(int amount);
    void AddMoney(int amount);

private:
    void LoadStoryData();
    void CheckLevelUp();
    void UnlockMissions();

private:
    std::vector<StoryMission> m_Missions;
    StoryMission* m_CurrentMission;
    
    int m_PlayerLevel;
    int m_PlayerExperience;
    int m_PlayerMoney;
    
    int m_ExperienceToNextLevel;
};

} // namespace game
} // namespace bf
