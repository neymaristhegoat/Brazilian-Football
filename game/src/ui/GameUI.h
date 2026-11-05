#pragma once

#include <memory>
#include <string>

namespace bf {
namespace game {

class GameUI {
public:
    GameUI();
    ~GameUI();

    bool Initialize();
    void Shutdown();
    void Update(float deltaTime);
    void Render();

    // Menu screens
    void ShowMainMenu();
    void ShowPauseMenu();
    void ShowSettingsMenu();
    void ShowMultiplayerLobby();

    // HUD
    void ShowMatchHUD();
    void HideMatchHUD();
    void UpdateScore(int homeScore, int awayScore);
    void UpdateMatchTime(float time);

    // Notifications
    void ShowNotification(const std::string& message, float duration = 3.0f);
    void ShowGoalNotification(const std::string& teamName);

private:
    bool m_ShowMainMenu;
    bool m_ShowPauseMenu;
    bool m_ShowMatchHUD;
    
    int m_HomeScore;
    int m_AwayScore;
    float m_MatchTime;
};

} // namespace game
} // namespace bf
