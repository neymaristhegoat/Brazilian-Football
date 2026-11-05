#include "network/NetworkManager.h"
#include "core/Logger.h"

namespace bf {
namespace network {

// NetworkClient
NetworkClient::NetworkClient()
    : m_Connected(false)
    , m_ClientID(0)
    , m_Socket(nullptr)
{
}

NetworkClient::~NetworkClient() {
    Disconnect();
}

bool NetworkClient::Connect(const std::string& address, uint16_t port) {
    BF_LOG_INFO("Connecting to server {}:{}...", address, port);
    // TODO: Implement socket connection
    m_Connected = true;
    return true;
}

void NetworkClient::Disconnect() {
    if (m_Connected) {
        BF_LOG_INFO("Disconnecting from server...");
        // TODO: Close socket
        m_Connected = false;
    }
}

void NetworkClient::Send(const NetworkMessage& message) {
    if (!m_Connected) return;
    // TODO: Send message over socket
}

void NetworkClient::Update() {
    if (!m_Connected) return;
    // TODO: Receive and process messages
}

// NetworkServer
NetworkServer::NetworkServer()
    : m_Running(false)
    , m_MaxClients(32)
    , m_Socket(nullptr)
{
}

NetworkServer::~NetworkServer() {
    Stop();
}

bool NetworkServer::Start(uint16_t port, int maxClients) {
    BF_LOG_INFO("Starting server on port {}...", port);
    m_MaxClients = maxClients;
    // TODO: Create listening socket
    m_Running = true;
    return true;
}

void NetworkServer::Stop() {
    if (m_Running) {
        BF_LOG_INFO("Stopping server...");
        // TODO: Close all connections
        m_Clients.clear();
        m_Running = false;
    }
}

void NetworkServer::Broadcast(const NetworkMessage& message) {
    for (uint32_t clientID : m_Clients) {
        SendTo(clientID, message);
    }
}

void NetworkServer::SendTo(uint32_t clientID, const NetworkMessage& message) {
    // TODO: Send message to specific client
}

void NetworkServer::Update() {
    if (!m_Running) return;
    // TODO: Accept new connections and process messages
}

// NetworkManager
NetworkManager::NetworkManager()
    : m_Mode(NetworkMode::None)
{
}

NetworkManager::~NetworkManager() {
    Shutdown();
}

bool NetworkManager::Initialize() {
    BF_LOG_INFO("Initializing network manager...");
    // TODO: Initialize networking library (Enet, raw sockets, etc)
    return true;
}

void NetworkManager::Shutdown() {
    BF_LOG_INFO("Shutting down network manager...");
    Disconnect();
}

void NetworkManager::Update() {
    if (m_Server) m_Server->Update();
    if (m_Client) m_Client->Update();
}

bool NetworkManager::StartServer(uint16_t port, int maxClients) {
    m_Server = std::make_unique<NetworkServer>();
    if (m_Server->Start(port, maxClients)) {
        m_Mode = NetworkMode::Server;
        return true;
    }
    m_Server.reset();
    return false;
}

bool NetworkManager::ConnectToServer(const std::string& address, uint16_t port) {
    m_Client = std::make_unique<NetworkClient>();
    if (m_Client->Connect(address, port)) {
        m_Mode = NetworkMode::Client;
        return true;
    }
    m_Client.reset();
    return false;
}

void NetworkManager::Disconnect() {
    if (m_Server) {
        m_Server->Stop();
        m_Server.reset();
    }
    if (m_Client) {
        m_Client->Disconnect();
        m_Client.reset();
    }
    m_Mode = NetworkMode::None;
}

} // namespace network
} // namespace bf
