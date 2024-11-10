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

bool Server::shutDown() {
    if(_host == nullptr) {
        return true;
    }
    // try to disconnect clients smoothly
    for(auto keyPair : _clients) {
        enet_peer_disconnect(keyPair.second, 0);
    }
    // wait for disconnects to be acknowledged
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
                std::cout << "Server::shutDown() - Successfully disconnected client ID " << event.peer->incomingPeerID << " from server" << std::endl;
                enet_peer_disconnect(event.peer, 0);
                _clients.erase(event.peer->incomingPeerID);
            }
            else if(event.type == ENET_EVENT_TYPE_CONNECT) {
                std::cout << "Server::shutDown() - Client ID " << event.peer->incomingPeerID << " connected during shut down, disconnecting" << std::endl;
                enet_peer_disconnect(event.peer, 0);
                // add to clients for when we receive disconnect event
                _clients[event.peer->incomingPeerID] = event.peer;
            }
        }
        else if(res < 0) {
            std::cout << "Server::shutDown() - Error encountered while polling" << std::endl;
            break;
        }
        else {
            if(_clients.empty()) {
                std::cout << "Server::shutDown() - All clients disconnected, shutting down server" << std::endl;
                success = true;
                break;
            }
        }
    }
    
    if(success == false) {
        std::cout << "Server::shutDown() - Failed to disconnect all clients, forcing shutdown" << std::endl;
        for(auto keyPair : _clients) {
            std::cout << "Server::shutDown() - Forcibly disconnecting client ID " << keyPair.first << std::endl;
            enet_peer_reset(keyPair.second);
        }
    }

    _clients.clear();
    enet_host_destroy(_host);
    _host = nullptr;

    return success;
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

                std::string str = "Client ID " + std::to_string(event.peer->incomingPeerID) + " has connected to server";
                Message msg(std::vector<uint8_t>(str.begin(), str.end()));
                broadcastMessage(DeliveryType::RELIABLE, msg);
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

bool Server::sendMessage(uint32_t clientId, DeliveryType deliveryType, Message message) {
    auto client = getClient(clientId);
    if(client == nullptr) {
        std::cout << "Server::sendPacket() - Client ID not connected (" << client << ")" << std::endl;
        return false;
    }
    uint32_t channel = 0;
    uint32_t flags = 0;
    if(deliveryType == DeliveryType::RELIABLE) {
        channel = RELIABLE_CHANNEL;
        flags = ENET_PACKET_FLAG_RELIABLE;
    }
    else if(deliveryType == DeliveryType::UNRELIABLE) {
        channel = UNRELIABLE_CHANNEL;
        flags = ENET_PACKET_FLAG_UNSEQUENCED;
    }
    else {
        std::cout << "Server::sendPacket() - Invalid delivery type!" << std::endl;
        return false;
    }

    ENetPacket* packet = enet_packet_create(&message.getData()[0], message.getData().size(), flags);
    int res = enet_peer_send(client, channel, packet);
    if(res != 0) {
        std::cout << "Server::sendPacket() - Failed to send packet! Return code " << res << std::endl;
        return false;
    }
    enet_host_flush(_host);
    return true;
}

bool Server::broadcastMessage(DeliveryType deliveryType, Message message) {
    if(numClients() == 0) {
        return true;
    }
    uint32_t channel = 0;
    uint32_t flags = 0;
    if(deliveryType == DeliveryType::RELIABLE) {
        channel = RELIABLE_CHANNEL;
        flags = ENET_PACKET_FLAG_RELIABLE;
    }
    else if(deliveryType == DeliveryType::UNRELIABLE) {
        channel = UNRELIABLE_CHANNEL;
        flags = ENET_PACKET_FLAG_UNSEQUENCED;
    }
    else {
        std::cout << "Server::sendPacket() - Invalid delivery type!" << std::endl;
        return false;
    }

    ENetPacket* packet = enet_packet_create(&message.getData()[0], message.getData().size(), flags);
    enet_host_broadcast(_host, channel, packet);
    enet_host_flush(_host);
    return true;
}

bool Server::isRunning() {
    return _host != nullptr;
}

bool Server::numClients() {
    return _host->peerCount;
}

ENetPeer* Server::getClient(uint32_t client) {
    return _clients[client];
}