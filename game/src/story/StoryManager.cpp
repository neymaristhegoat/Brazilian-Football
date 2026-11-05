#include "story/StoryManager.h"
#include "core/Logger.h"

namespace bf {
namespace game {

StoryManager::StoryManager()
    : m_CurrentMission(nullptr)
    , m_PlayerLevel(1)
    , m_PlayerExperience(0)
    , m_PlayerMoney(0)
    , m_ExperienceToNextLevel(1000)
{
}

StoryManager::~StoryManager() {
}

bool StoryManager::Initialize() {
    BF_LOG_INFO("Initializing story manager...");
    LoadStoryData();
    return true;
}

void StoryManager::Shutdown() {
    BF_LOG_INFO("Shutting down story manager...");
}

void StoryManager::Update(float deltaTime) {
    // TODO: Update current mission progress
}

void StoryManager::StartMission(const std::string& missionID) {
    auto* mission = GetMission(missionID);
    if (mission && mission->status == MissionStatus::Available) {
        mission->status = MissionStatus::InProgress;
        m_CurrentMission = mission;
        BF_LOG_INFO("Started mission: {}", mission->name);
    }
}

void StoryManager::CompleteMission(const std::string& missionID) {
    auto* mission = GetMission(missionID);
    if (mission && mission->status == MissionStatus::InProgress) {
        mission->status = MissionStatus::Completed;
        
        AddExperience(mission->experienceReward);
        AddMoney(mission->moneyReward);
        
        BF_LOG_INFO("Completed mission: {}", mission->name);
        
        m_CurrentMission = nullptr;
        UnlockMissions();
    }
}

void StoryManager::FailMission(const std::string& missionID) {
    auto* mission = GetMission(missionID);
    if (mission && mission->status == MissionStatus::InProgress) {
        mission->status = MissionStatus::Failed;
        BF_LOG_INFO("Failed mission: {}", mission->name);
        m_CurrentMission = nullptr;
    }
}

StoryMission* StoryManager::GetMission(const std::string& missionID) {
    for (auto& mission : m_Missions) {
        if (mission.id == missionID) {
            return &mission;
        }
    }
    return nullptr;
}

std::vector<StoryMission*> StoryManager::GetAvailableMissions() {
    std::vector<StoryMission*> available;
    for (auto& mission : m_Missions) {
        if (mission.status == MissionStatus::Available) {
            available.push_back(&mission);
        }
    }
    return available;
}

void StoryManager::AddExperience(int amount) {
    m_PlayerExperience += amount;
    BF_LOG_INFO("Gained {} experience", amount);
    CheckLevelUp();
}

void StoryManager::AddMoney(int amount) {
    m_PlayerMoney += amount;
    BF_LOG_INFO("Gained {} money", amount);
}

void StoryManager::LoadStoryData() {
    // TODO: Load story missions from data files
    BF_LOG_DEBUG("Loading story data...");
    
    // Example mission
    StoryMission intro;
    intro.id = "intro_match";
    intro.name = "First Match";
    intro.description = "Play your first match in the streets of Brazil";
    intro.type = MissionType::Match;
    intro.status = MissionStatus::Available;
    intro.experienceReward = 500;
    intro.moneyReward = 100;
    m_Missions.push_back(intro);
}

void StoryManager::CheckLevelUp() {
    while (m_PlayerExperience >= m_ExperienceToNextLevel) {
        m_PlayerLevel++;
        m_PlayerExperience -= m_ExperienceToNextLevel;
        m_ExperienceToNextLevel = static_cast<int>(m_ExperienceToNextLevel * 1.5f);
        
        BF_LOG_INFO("Level up! Now level {}", m_PlayerLevel);
    }
}

void StoryManager::UnlockMissions() {
    // Check which missions should be unlocked
    for (auto& mission : m_Missions) {
        if (mission.status == MissionStatus::Locked) {
            bool canUnlock = true;
            for (const auto& reqID : mission.requiredMissions) {
                auto* req = GetMission(reqID);
                if (!req || req->status != MissionStatus::Completed) {
                    canUnlock = false;
                    break;
                }
            }
            
            if (canUnlock) {
                mission.status = MissionStatus::Available;
                BF_LOG_INFO("Unlocked mission: {}", mission.name);
            }
        }
    }
}

} // namespace game
} // namespace bf
