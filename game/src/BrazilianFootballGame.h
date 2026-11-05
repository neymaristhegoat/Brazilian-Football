/**
 * Game Module - Main Game Entry
 * Coordinates all game systems
 */

#pragma once

#include "core/Application.h"
#include <memory>

namespace bf {
namespace game {

class Player;
class Team;
class Match;
class GameUI;
class GameState;

class BrazilianFootballGame {
public:
    BrazilianFootballGame();
    ~BrazilianFootballGame();

    bool Initialize();
    void Shutdown();

    void Update(float deltaTime);
    void Render();

    // Game mode management
    void StartMainMenu();
    void StartStoryMode();
    void StartMultiplayer();
    void StartHeader1v1();
    void StartOpenWorld();

    GameState* GetGameState() const { return m_GameState.get(); }

private:
    std::unique_ptr<GameState> m_GameState;
    std::unique_ptr<GameUI> m_UI;
};

} // namespace game
} // namespace bf
