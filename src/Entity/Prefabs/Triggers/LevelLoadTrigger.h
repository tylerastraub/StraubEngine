#pragma once

#include "rect2.h"

#include <entt/entity/registry.hpp>

namespace prefab {
    class LevelLoadTrigger {
    public:
        LevelLoadTrigger() = default;
        ~LevelLoadTrigger() = default;

        static entt::entity create(entt::registry& ecs);
        static entt::entity create(entt::registry& ecs, strb::rect2f triggerRect, std::string levelPath, int playerSpawnID);

    private:

    };
}