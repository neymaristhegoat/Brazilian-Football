#include "gameplay/GameState.h"
#include "gameplay/Match.h"
#include "core/Logger.h"

namespace bf {
namespace game {

GameState::GameState()
    : m_CurrentMode(GameMode::None)
    , m_MatchState(MatchState::PreMatch)
    , m_ControlledPlayer(nullptr)
    , m_GameTime(0.0f)
    , m_MatchTime(0.0f)
{
}

GameState::~GameState() {
}

bool GameState::Initialize() {
    BF_LOG_INFO("Initializing game state...");
    return true;
}

void GameState::Shutdown() {
    BF_LOG_INFO("Shutting down game state...");
}

void GameState::Update(float deltaTime) {
    m_GameTime += deltaTime;
    
    if (m_CurrentMatch && m_MatchState == MatchState::Playing) {
        m_MatchTime += deltaTime;
        m_CurrentMatch->Update(deltaTime);
    }
}

void GameState::Render() {
    if (m_CurrentMatch) {
        m_CurrentMatch->Render();
    }
}

void GameState::SetGameMode(GameMode mode) {
    BF_LOG_INFO("Changing game mode to {}", static_cast<int>(mode));
    m_CurrentMode = mode;
}

void GameState::StartMatch(Team* homeTeam, Team* awayTeam) {
    BF_LOG_INFO("Starting match...");
    m_CurrentMatch = std::make_unique<Match>(homeTeam, awayTeam);
    m_MatchState = MatchState::KickOff;
    m_MatchTime = 0.0f;
}

void GameState::EndMatch() {
    BF_LOG_INFO("Ending match...");
    m_CurrentMatch.reset();
    m_MatchState = MatchState::PreMatch;
}

} // namespace game
} // namespace bf
