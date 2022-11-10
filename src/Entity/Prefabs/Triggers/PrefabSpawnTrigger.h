#ifndef PREFAB_SPAWN_TRIGGER_H
#define PREFAB_SPAWN_TRIGGER_H

#include "vec2.h"
#include "PrefabType.h"

#include <cstdint>
#include <SDL.h>
#include <string>

using Entity = std::uint16_t;

namespace prefab {
    class PrefabSpawnTrigger {
    public:
        PrefabSpawnTrigger() = default;
        ~PrefabSpawnTrigger() = default;

        static Entity create();
        static Entity create(
            SDL_Rect triggerRect,
            bool triggerOnce,
            bool entityMustBeGrounded,
            PrefabType prefabType,
            strb::vec2 prefabSpawnPos,
            std::string prefabValue
        );

    private:

    };
}

#endif