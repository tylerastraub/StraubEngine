#ifndef SYSTEM_H
#define SYSTEM_H

#include "Audio.h"

#include <cstdint>
#include <set>

using Entity = std::uint16_t;

class System {
public:
    std::set<Entity, std::greater<Entity>> _entities;
    Audio* _audioPlayer = nullptr;
};

#endif