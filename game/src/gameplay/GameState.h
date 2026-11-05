#pragma once

#include <memory>
#include <vector>
#include "gameplay/Player.h"

namespace bf {
namespace game {

enum class GameMode {
    None,
    MainMenu,
    StoryMode,
    Multiplayer,
    Header1v1,
    OpenWorld,
    Training
};

enum class MatchState {
    PreMatch,
    KickOff,
    Playing,
    HalfTime,
    FullTime,
    Paused
};

class Team;
class Match;
class Ball;

class GameState {
public:
    GameState();
    ~GameState();

    bool Initialize();
    void Shutdown();
    void Update(float deltaTime);
    void Render();

    // Mode management
    void SetGameMode(GameMode mode);
    GameMode GetGameMode() const { return m_CurrentMode; }

    // Match management
    void StartMatch(Team* homeTeam, Team* awayTeam);
    void EndMatch();
    Match* GetCurrentMatch() { return m_CurrentMatch.get(); }

    // Player management
    void SetControlledPlayer(Player* player) { m_ControlledPlayer = player; }
    Player* GetControlledPlayer() const { return m_ControlledPlayer; }

private:
    GameMode m_CurrentMode;
    MatchState m_MatchState;
    
    std::unique_ptr<Match> m_CurrentMatch;
    Player* m_ControlledPlayer;
    
    float m_GameTime;
    float m_MatchTime;
};

} // namespace game
} // namespace bf
