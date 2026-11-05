#pragma once

#include <memory>
#include <string>
#include <vector>
#include <cstdint>

namespace bf {

namespace network {
class NetworkManager;
}

namespace game {

class GameState;
class Player;
class Team;

enum class MultiplayerMode {
    QuickMatch,
    Ranked,
    OpenWorld,
    Header1v1,
    Custom
};

struct MultiplayerSession {
    std::string sessionID;
    std::string hostName;
    MultiplayerMode mode;
    int currentPlayers;
    int maxPlayers;
    bool isPublic;
};

class MultiplayerManager {
public:
    MultiplayerManager();
    ~MultiplayerManager();

    bool Initialize();
    void Shutdown();
    void Update(float deltaTime);

    // Session management
    bool CreateSession(MultiplayerMode mode, int maxPlayers, bool isPublic);
    bool JoinSession(const std::string& sessionID);
    void LeaveSession();

    std::vector<MultiplayerSession> GetAvailableSessions();

    // Player management
    void SendPlayerInput(Player* player);
    void SyncPlayerState(Player* player);

    // Match synchronization
    void StartMatch();
    void SyncMatchState(GameState* state);

    bool IsConnected() const { return m_Connected; }
    bool IsHost() const { return m_IsHost; }

private:
    void OnPlayerJoined(uint32_t clientID);
    void OnPlayerLeft(uint32_t clientID);
    void OnMessageReceived(uint32_t clientID, const void* data, size_t size);

private:
    network::NetworkManager* m_NetworkManager;
    bool m_Connected;
    bool m_IsHost;
    
    std::string m_SessionID;
    MultiplayerSession m_CurrentSession;
};

} // namespace game
} // namespace bf
