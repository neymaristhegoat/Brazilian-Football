#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <cstdint>

namespace bf {
namespace network {

enum class NetworkMode {
    None,
    Client,
    Server,
    Host
};

enum class MessageType : uint8_t {
    Connect = 0,
    Disconnect,
    PlayerJoin,
    PlayerLeave,
    GameState,
    PlayerInput,
    EntityUpdate,
    Custom
};

struct NetworkMessage {
    MessageType type;
    uint32_t senderID;
    std::vector<uint8_t> data;
};

class NetworkClient {
public:
    NetworkClient();
    ~NetworkClient();

    bool Connect(const std::string& address, uint16_t port);
    void Disconnect();
    bool IsConnected() const { return m_Connected; }

    void Send(const NetworkMessage& message);
    void Update();

    uint32_t GetClientID() const { return m_ClientID; }

    using MessageCallback = std::function<void(const NetworkMessage&)>;
    void SetMessageCallback(MessageCallback callback) { m_MessageCallback = callback; }

private:
    bool m_Connected;
    uint32_t m_ClientID;
    void* m_Socket;
    MessageCallback m_MessageCallback;
};

class NetworkServer {
public:
    NetworkServer();
    ~NetworkServer();

    bool Start(uint16_t port, int maxClients = 32);
    void Stop();
    bool IsRunning() const { return m_Running; }

    void Broadcast(const NetworkMessage& message);
    void SendTo(uint32_t clientID, const NetworkMessage& message);
    void Update();

    int GetClientCount() const { return m_Clients.size(); }
    int GetMaxClients() const { return m_MaxClients; }

    using ClientConnectedCallback = std::function<void(uint32_t)>;
    using ClientDisconnectedCallback = std::function<void(uint32_t)>;
    using MessageCallback = std::function<void(uint32_t, const NetworkMessage&)>;

    void SetClientConnectedCallback(ClientConnectedCallback callback) { m_OnClientConnected = callback; }
    void SetClientDisconnectedCallback(ClientDisconnectedCallback callback) { m_OnClientDisconnected = callback; }
    void SetMessageCallback(MessageCallback callback) { m_MessageCallback = callback; }

private:
    bool m_Running;
    int m_MaxClients;
    void* m_Socket;
    std::vector<uint32_t> m_Clients;
    
    ClientConnectedCallback m_OnClientConnected;
    ClientDisconnectedCallback m_OnClientDisconnected;
    MessageCallback m_MessageCallback;
};

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();

    bool Initialize();
    void Shutdown();
    void Update();

    bool StartServer(uint16_t port, int maxClients = 32);
    bool ConnectToServer(const std::string& address, uint16_t port);
    void Disconnect();

    NetworkMode GetMode() const { return m_Mode; }
    bool IsServer() const { return m_Mode == NetworkMode::Server || m_Mode == NetworkMode::Host; }
    bool IsClient() const { return m_Mode == NetworkMode::Client || m_Mode == NetworkMode::Host; }

    NetworkServer* GetServer() { return m_Server.get(); }
    NetworkClient* GetClient() { return m_Client.get(); }

private:
    NetworkMode m_Mode;
    std::unique_ptr<NetworkServer> m_Server;
    std::unique_ptr<NetworkClient> m_Client;
};

} // namespace network
} // namespace bf
