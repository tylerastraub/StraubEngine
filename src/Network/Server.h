#pragma once

#include "Message.h"
#include "DeliveryType.h"

#include <enet/enet.h>
#include <cstdint>
#include <chrono>
#include <string>
#include <unordered_map>

class Server {
public:
    Server() = default;
    ~Server();

    std::string addressToString(const ENetAddress* address);

    bool start(uint32_t port);
    bool shutDown();
    void poll();
    bool sendMessage(uint32_t peerId, DeliveryType deliveryType, Message message);
    bool broadcastMessage(DeliveryType deliveryType, Message message);

    bool isRunning();
    bool numClients();
    ENetPeer* getClient(uint32_t clientId);

private:
    const uint32_t MAX_CONNECTIONS = 32;
    const std::time_t TIMEOUT_MS = 5000;
    const uint8_t RELIABLE_CHANNEL = 0;
    const uint8_t UNRELIABLE_CHANNEL = 1;
    const uint8_t NUM_CHANNELS = 2;

    ENetHost* _host = nullptr;
    uint32_t _currentMessageId = 0;

    std::unordered_map<uint32_t, ENetPeer*> _clients;

};