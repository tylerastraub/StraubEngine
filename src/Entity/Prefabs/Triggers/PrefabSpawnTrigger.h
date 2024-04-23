#pragma once

#include "vec2.h"
#include "PrefabType.h"
#include "rect2.h"

#include <cstdint>
#include <string>
#include <entt/entity/registry.hpp>

namespace prefab {
    class PrefabSpawnTrigger {
    public:
        PrefabSpawnTrigger() = default;
        ~PrefabSpawnTrigger() = default;

        static entt::entity create(entt::registry& ecs);
        static entt::entity create(
            entt::registry& ecs,
            strb::rect2f triggerRect,
            bool triggerOnce,
            bool entityMustBeGrounded,
            PrefabType prefabType,
            strb::vec2f prefabSpawnPos,
            std::string prefabValue
        );

    private:

    };
}