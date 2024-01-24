#pragma once

#include "Level.h"

#include <entt/entity/registry.hpp>

class LightSystem {
public:
    LightSystem() = default;
    ~LightSystem() = default;

    void update(entt::registry& ecs, Level& level);
    void updateLightSources(entt::registry& ecs, Level& level);
    uint16_t addLightSource(Level& level, Light light);
    void removeLightSource(Level& level, Light light);

private:

};