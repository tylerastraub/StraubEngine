#pragma once

#include <enet/enet.h>
#include <cstdint>
#include <chrono>
#include <string>

class Client {
public:
    Client();
    ~Client();

    bool connect(const std::string& host, uint32_t port);
    bool disconnect();
    void poll();

    bool isConnected();

private:
    const std::time_t TIMEOUT_MS = 5000;
    const uint8_t RELIABLE_CHANNEL = 0;
    const uint8_t UNRELIABLE_CHANNEL = 1;
    const uint8_t NUM_CHANNELS = 2;

    ENetHost* _host = nullptr;
    ENetPeer* _server = nullptr;

};