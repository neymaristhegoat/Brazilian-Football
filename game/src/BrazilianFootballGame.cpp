#include "BrazilianFootballGame.h"
#include "core/Logger.h"
#include "gameplay/GameState.h"
#include "ui/GameUI.h"

namespace bf {
namespace game {

BrazilianFootballGame::BrazilianFootballGame()
{
}

BrazilianFootballGame::~BrazilianFootballGame() {
    Shutdown();
}

bool BrazilianFootballGame::Initialize() {
    BF_LOG_INFO("Initializing Brazilian Football Game...");

    m_GameState = std::make_unique<GameState>();
    m_UI = std::make_unique<GameUI>();

    if (!m_GameState->Initialize()) {
        BF_LOG_ERROR("Failed to initialize game state");
        return false;
    }

    if (!m_UI->Initialize()) {
        BF_LOG_ERROR("Failed to initialize UI");
        return false;
    }

    BF_LOG_INFO("Game initialization complete");
    return true;
}

void BrazilianFootballGame::Shutdown() {
    BF_LOG_INFO("Shutting down game...");
    
    if (m_UI) m_UI->Shutdown();
    if (m_GameState) m_GameState->Shutdown();
}

void BrazilianFootballGame::Update(float deltaTime) {
    if (m_GameState) {
        m_GameState->Update(deltaTime);
    }
    
    if (m_UI) {
        m_UI->Update(deltaTime);
    }
}

void BrazilianFootballGame::Render() {
    if (m_GameState) {
        m_GameState->Render();
    }
    
    if (m_UI) {
        m_UI->Render();
    }
}

void BrazilianFootballGame::StartMainMenu() {
    BF_LOG_INFO("Starting main menu...");
    // TODO: Load main menu scene
}

void BrazilianFootballGame::StartStoryMode() {
    BF_LOG_INFO("Starting story mode...");
    // TODO: Load story mode
}

void BrazilianFootballGame::StartMultiplayer() {
    BF_LOG_INFO("Starting multiplayer...");
    // TODO: Load multiplayer lobby
}

void BrazilianFootballGame::StartHeader1v1() {
    BF_LOG_INFO("Starting Header 1v1 mode...");
    // TODO: Load 1v1 mode
}

void BrazilianFootballGame::StartOpenWorld() {
    BF_LOG_INFO("Starting open world mode...");
    // TODO: Load open world
}

} // namespace game
} // namespace bf
