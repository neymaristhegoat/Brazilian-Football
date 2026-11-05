#pragma once

#include <string>
#include <vector>
#include <memory>

namespace bf {
namespace game {

class Player;

enum class Formation {
    F_4_4_2,
    F_4_3_3,
    F_3_5_2,
    F_4_2_3_1,
    F_5_3_2
};

struct TeamStats {
    int goalsScored = 0;
    int goalsConceded = 0;
    int shots = 0;
    int shotsOnTarget = 0;
    int possession = 50;
    int passes = 0;
    int tackles = 0;
    int fouls = 0;
    int yellowCards = 0;
    int redCards = 0;
};

class Team {
public:
    Team();
    Team(const std::string& name);
    ~Team();

    void Initialize();
    void Update(float deltaTime);

    // Players
    void AddPlayer(std::shared_ptr<Player> player);
    void RemovePlayer(Player* player);
    Player* GetPlayer(int index);
    const std::vector<std::shared_ptr<Player>>& GetPlayers() const { return m_Players; }

    // Formation
    void SetFormation(Formation formation);
    Formation GetFormation() const { return m_Formation; }

    // Properties
    void SetName(const std::string& name) { m_Name = name; }
    const std::string& GetName() const { return m_Name; }

    void SetColor(float r, float g, float b);
    
    TeamStats& GetStats() { return m_Stats; }
    const TeamStats& GetStats() const { return m_Stats; }

    int GetScore() const { return m_Stats.goalsScored; }

private:
    std::string m_Name;
    Formation m_Formation;
    std::vector<std::shared_ptr<Player>> m_Players;
    TeamStats m_Stats;
    
    float m_ColorR, m_ColorG, m_ColorB;
};

} // namespace game
} // namespace bf
