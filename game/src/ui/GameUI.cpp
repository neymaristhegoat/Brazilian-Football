#include "ui/GameUI.h"
#include "core/Logger.h"

namespace bf {
namespace game {

GameUI::GameUI()
    : m_ShowMainMenu(true)
    , m_ShowPauseMenu(false)
    , m_ShowMatchHUD(false)
    , m_HomeScore(0)
    , m_AwayScore(0)
    , m_MatchTime(0.0f)
{
}

GameUI::~GameUI() {
}

bool GameUI::Initialize() {
    BF_LOG_INFO("Initializing game UI...");
    // TODO: Load UI resources, fonts, textures
    return true;
}

void GameUI::Shutdown() {
    BF_LOG_INFO("Shutting down game UI...");
}

void GameUI::Update(float deltaTime) {
    // TODO: Update UI animations, transitions
}

void GameUI::Render() {
    if (m_ShowMainMenu) {
        // TODO: Render main menu
    }
    
    if (m_ShowPauseMenu) {
        // TODO: Render pause menu
    }
    
    if (m_ShowMatchHUD) {
        // TODO: Render match HUD (score, time, player stamina, etc)
    }
}

void GameUI::ShowMainMenu() {
    m_ShowMainMenu = true;
    m_ShowMatchHUD = false;
    BF_LOG_DEBUG("Showing main menu");
}

void GameUI::ShowPauseMenu() {
    m_ShowPauseMenu = true;
    BF_LOG_DEBUG("Showing pause menu");
}

void GameUI::ShowSettingsMenu() {
    BF_LOG_DEBUG("Showing settings menu");
}

void GameUI::ShowMultiplayerLobby() {
    BF_LOG_DEBUG("Showing multiplayer lobby");
}

void GameUI::ShowMatchHUD() {
    m_ShowMatchHUD = true;
    m_ShowMainMenu = false;
    BF_LOG_DEBUG("Showing match HUD");
}

void GameUI::HideMatchHUD() {
    m_ShowMatchHUD = false;
    BF_LOG_DEBUG("Hiding match HUD");
}

void GameUI::UpdateScore(int homeScore, int awayScore) {
    m_HomeScore = homeScore;
    m_AwayScore = awayScore;
}

void GameUI::UpdateMatchTime(float time) {
    m_MatchTime = time;
}

void GameUI::ShowNotification(const std::string& message, float duration) {
    BF_LOG_INFO("Notification: {}", message);
    // TODO: Display notification UI
}

void GameUI::ShowGoalNotification(const std::string& teamName) {
    BF_LOG_INFO("GOAL! {}", teamName);
    // TODO: Show goal celebration UI
}

} // namespace game
} // namespace bf
