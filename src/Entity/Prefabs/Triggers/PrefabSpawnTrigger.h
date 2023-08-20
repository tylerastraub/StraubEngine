#pragma once

#include "vec2.h"
#include "PrefabType.h"
#include "rect2.h"

#include <cstdint>
#include <string>

using Entity = std::uint16_t;

namespace prefab {
    class PrefabSpawnTrigger {
    public:
        PrefabSpawnTrigger() = default;
        ~PrefabSpawnTrigger() = default;

        static Entity create();
        static Entity create(
            strb::rect2i triggerRect,
            bool triggerOnce,
            bool entityMustBeGrounded,
            PrefabType prefabType,
            strb::vec2f prefabSpawnPos,
            std::string prefabValue
        );

    private:

    };
}