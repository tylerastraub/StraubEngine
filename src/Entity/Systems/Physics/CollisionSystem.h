#pragma once

#include "Level.h"
#include "Audio.h"

#include <memory>
#include <entt/entity/registry.hpp>

class CollisionSystem {
public:
    CollisionSystem() = default;
    ~CollisionSystem() = default;

    void updateLevelCollisionsOnXAxis(entt::registry& ecs, Level level);
    void updateLevelCollisionsOnYAxis(entt::registry& ecs, Level level);

private:

};