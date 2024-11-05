#include "Client.h"

#include <iostream>

Client::Client() {
    _host = enet_host_create(
        NULL,
        1,
        NUM_CHANNELS,
        0,
        0
    );

    if(_host == nullptr) {
        std::cout << "Error creating host for client!" << std::endl;
    }
}

Client::~Client() {
    disconnect();
    enet_host_destroy(_host);
    _host = nullptr;
}

bool Client::connect(const std::string& host, uint32_t port) {
    if(isConnected()) {
        std::cout << "Client::connect() - Client is already connected to a server!" << std::endl;
        return false;
    }

    ENetAddress address;
    enet_address_set_host(&address, host.c_str());
    address.port = port;

    _server = enet_host_connect(_host, &address, NUM_CHANNELS, 0);
    if(_server == nullptr) {
        std::cout << "Client::connect() - Error connecting to peer!" << std::endl;
        return false;       
    }

    ENetEvent event;
    if(enet_host_service(_host, &event, TIMEOUT_MS) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
        std::cout << "Client::connect() - Connected to " << host << ":" << port << std::endl;
        enet_host_flush(_host);
        return true;
    }
    std::cout << "Client::connect() - Failed to connect to " << host << ":" << port << "! Error: Connection timed out (" << TIMEOUT_MS << "ms)" << std::endl;
    enet_peer_reset(_server);
    _server = nullptr;
    return false;
}

bool Client::disconnect() {
    if(!isConnected()) {
        return true;
    }
    enet_peer_disconnect(_server, 0);

    ENetEvent event;
    auto timestamp = std::chrono::high_resolution_clock::now();
    bool success = false;
    while(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - timestamp).count() < TIMEOUT_MS) {
        int32_t res = enet_host_service(_host, &event, 0);
        if(res > 0) {
            if(event.type == ENET_EVENT_TYPE_RECEIVE) {
                // while disconnecting, destroy any packets we receive
                enet_packet_destroy(event.packet);
            }
            else if(event.type == ENET_EVENT_TYPE_DISCONNECT) {
                std::cout << "Client::disconnect() - Successfully disconnected client from server" << std::endl;
                success = true;
                break;
            }
        }
        else if(res < 0) {
            std::cout << "Client::disconnect() - Error encountered while polling" << std::endl;
            break;
        }
    }

    if(success == false) {
        std::cout << "Client::disconnect() - disconnect was not acknowledged by server, shutdown forced" << std::endl;
        enet_peer_reset(_server);
    }
    _server = nullptr;
    return success;
}

void Client::poll() {
    if(isConnected() == false) {
        return;
    }
    ENetEvent event;
    while(true) {
        int32_t res = enet_host_service(_host, &event, 0);
        if(res > 0) {
            if(event.type == ENET_EVENT_TYPE_RECEIVE) {
                // todo: process packet
                enet_packet_destroy(event.packet);
            }
            else if(event.type == ENET_EVENT_TYPE_DISCONNECT) {
                std::cout << "Client::poll() - Connection to server has been lost" << std::endl;
                _server = nullptr;
            }
        }
        else if(res < 0) {
            std::cout << "Client::poll() - Error encountered while polling" << std::endl;
            break;
        }
        else {
            // no event
            break;
        }
    }
}

bool Client::isConnected() {
    if(_host) {
        return _host->connectedPeers > 0;
    }
    return false;
}