#include "Server.h"

#include <iostream>

Server::~Server() {
    shutDown();
}

std::string Server::addressToString(const ENetAddress* address) {
    uint8_t a = (uint8_t)(address->host);
    uint8_t b = (uint8_t)(address->host >> 8);
    uint8_t c = (uint8_t)(address->host >> 16);
    uint8_t d = (uint8_t)(address->host >> 24);
    return std::to_string(a) + "." + std::to_string(b) + "." + std::to_string(c) + "." + std::to_string(d) + ":" + std::to_string(address->port);
}

bool Server::start(uint32_t port) {
    ENetAddress address;
    enet_address_set_host(&address, "localhost"); // todo: dynamically set this
    address.port = port;

    _host = enet_host_create(
        &address,
        MAX_CONNECTIONS,
        NUM_CHANNELS,
        0,
        0
    );

    if(_host == nullptr) {
        std::cout << "Server::start() - Error creating ENet host!" << std::endl;
        return false;
    }

    std::string ip = addressToString(&address);
    std::cout << "Server::start() - Successfully started server at address " << ip << std::endl;

    return true;
}

void Server::shutDown() {
    enet_host_destroy(_host);
    _host = nullptr;
}

void Server::poll() {
    ENetEvent event;
    while(true) {
        // no timeout
        int32_t res = enet_host_service(_host, &event, 0);
        if(res > 0) {
            if(event.type == ENET_EVENT_TYPE_RECEIVE) {
                // received a packet
                std::cout << "Server::poll() - Received a packet of length " << event.packet->dataLength
                    << " containing " << event.packet->data << " from client ID " << event.peer->incomingPeerID << std::endl;
            }
            else if(event.type == ENET_EVENT_TYPE_CONNECT) {
                std::cout << "Server::poll() - Client connected from " << addressToString(&event.peer->address)
                    << ", " << _host->connectedPeers << " clients currently connected" << std::endl;
                _clients[event.peer->incomingPeerID] = event.peer;
            }
            else if(event.type == ENET_EVENT_TYPE_DISCONNECT) {
                std::cout << "Server::poll() - Client has disconnected from " << addressToString(&event.peer->address)
                    << ", " << _host->connectedPeers << " clients currently connected" << std::endl;
                _clients.erase(event.peer->incomingPeerID);
            }
        }
        else if(res < 0) {
            std::cout << "Server::poll() - Error encountered while polling" << std::endl;
            break;
        }
        else {
            // no event
            break;
        }
    }
}

bool Server::isRunning() {
    return _host != nullptr;
}