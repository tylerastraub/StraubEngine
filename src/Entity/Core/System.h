#pragma once

#include "Audio.h"

#include <cstdint>
#include <set>

using Entity = std::uint16_t;

class System {
public:
    virtual void onEntityDelete(Entity entity) {};

    std::set<Entity, std::greater<Entity>> _entities;
    Audio* _audioPlayer = nullptr;
};