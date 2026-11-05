#include "gameplay/Team.h"
#include "gameplay/Player.h"
#include "core/Logger.h"

namespace bf {
namespace game {

Team::Team()
    : m_Name("Team")
    , m_Formation(Formation::F_4_4_2)
    , m_ColorR(1.0f), m_ColorG(1.0f), m_ColorB(1.0f)
{
}

Team::Team(const std::string& name)
    : m_Name(name)
    , m_Formation(Formation::F_4_4_2)
    , m_ColorR(1.0f), m_ColorG(1.0f), m_ColorB(1.0f)
{
}

Team::~Team() {
}

void Team::Initialize() {
    BF_LOG_INFO("Initializing team: {}", m_Name);
    
    // Initialize all players
    for (auto& player : m_Players) {
        player->Initialize();
    }
}

void Team::Update(float deltaTime) {
    // Update all players
    for (auto& player : m_Players) {
        player->Update(deltaTime);
    }
}

void Team::AddPlayer(std::shared_ptr<Player> player) {
    m_Players.push_back(player);
    BF_LOG_DEBUG("Added player {} to team {}", player->GetName(), m_Name);
}

void Team::RemovePlayer(Player* player) {
    auto it = std::find_if(m_Players.begin(), m_Players.end(),
        [player](const std::shared_ptr<Player>& p) { return p.get() == player; });
    
    if (it != m_Players.end()) {
        m_Players.erase(it);
        BF_LOG_DEBUG("Removed player from team {}", m_Name);
    }
}

Player* Team::GetPlayer(int index) {
    if (index >= 0 && index < static_cast<int>(m_Players.size())) {
        return m_Players[index].get();
    }
    return nullptr;
}

void Team::SetFormation(Formation formation) {
    m_Formation = formation;
    BF_LOG_INFO("Team {} changed formation to {}", m_Name, static_cast<int>(formation));
    // TODO: Reposition players based on formation
}

void Team::SetColor(float r, float g, float b) {
    m_ColorR = r;
    m_ColorG = g;
    m_ColorB = b;
}

} // namespace game
} // namespace bf
