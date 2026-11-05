#include "multiplayer/MultiplayerManager.h"
#include "network/NetworkManager.h"
#include "gameplay/Player.h"
#include "gameplay/GameState.h"
#include "core/Logger.h"

namespace bf {
namespace game {

MultiplayerManager::MultiplayerManager()
    : m_NetworkManager(nullptr)
    , m_Connected(false)
    , m_IsHost(false)
{
}

MultiplayerManager::~MultiplayerManager() {
    Shutdown();
}

bool MultiplayerManager::Initialize() {
    BF_LOG_INFO("Initializing multiplayer manager...");
    
    m_NetworkManager = new network::NetworkManager();
    if (!m_NetworkManager->Initialize()) {
        BF_LOG_ERROR("Failed to initialize network manager");
        return false;
    }
    
    return true;
}

void MultiplayerManager::Shutdown() {
    BF_LOG_INFO("Shutting down multiplayer manager...");
    
    LeaveSession();
    
    if (m_NetworkManager) {
        m_NetworkManager->Shutdown();
        delete m_NetworkManager;
        m_NetworkManager = nullptr;
    }
}

void MultiplayerManager::Update(float deltaTime) {
    if (m_NetworkManager) {
        m_NetworkManager->Update();
    }
}

bool MultiplayerManager::CreateSession(MultiplayerMode mode, int maxPlayers, bool isPublic) {
    BF_LOG_INFO("Creating multiplayer session...");
    
    if (m_NetworkManager->StartServer(7777, maxPlayers)) {
        m_IsHost = true;
        m_Connected = true;
        
        m_CurrentSession.mode = mode;
        m_CurrentSession.maxPlayers = maxPlayers;
        m_CurrentSession.currentPlayers = 1;
        m_CurrentSession.isPublic = isPublic;
        
        BF_LOG_INFO("Session created successfully");
        return true;
    }
    
    return false;
}

bool MultiplayerManager::JoinSession(const std::string& sessionID) {
    BF_LOG_INFO("Joining multiplayer session: {}", sessionID);
    
    // TODO: Parse session info to get address
    if (m_NetworkManager->ConnectToServer("127.0.0.1", 7777)) {
        m_IsHost = false;
        m_Connected = true;
        m_SessionID = sessionID;
        
        BF_LOG_INFO("Joined session successfully");
        return true;
    }
    
    return false;
}

void MultiplayerManager::LeaveSession() {
    if (m_Connected) {
        BF_LOG_INFO("Leaving multiplayer session...");
        m_NetworkManager->Disconnect();
        m_Connected = false;
        m_IsHost = false;
    }
}

std::vector<MultiplayerSession> MultiplayerManager::GetAvailableSessions() {
    // TODO: Query available sessions from master server
    std::vector<MultiplayerSession> sessions;
    return sessions;
}

void MultiplayerManager::SendPlayerInput(Player* player) {
    if (!m_Connected) return;
    
    // TODO: Serialize and send player input
}

void MultiplayerManager::SyncPlayerState(Player* player) {
    if (!m_Connected) return;
    
    // TODO: Serialize and sync player state
}

void MultiplayerManager::StartMatch() {
    if (!m_IsHost) return;
    
    BF_LOG_INFO("Starting multiplayer match...");
    // TODO: Broadcast match start to all clients
}

void MultiplayerManager::SyncMatchState(GameState* state) {
    if (!m_IsHost) return;
    
    // TODO: Broadcast match state
}

void MultiplayerManager::OnPlayerJoined(uint32_t clientID) {
    BF_LOG_INFO("Player joined: {}", clientID);
    m_CurrentSession.currentPlayers++;
}

void MultiplayerManager::OnPlayerLeft(uint32_t clientID) {
    BF_LOG_INFO("Player left: {}", clientID);
    m_CurrentSession.currentPlayers--;
}

void MultiplayerManager::OnMessageReceived(uint32_t clientID, const void* data, size_t size) {
    // TODO: Handle incoming messages
}

} // namespace game
} // namespace bf
