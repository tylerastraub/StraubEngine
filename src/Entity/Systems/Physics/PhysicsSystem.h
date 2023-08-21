#pragma once

#include <entt/entity/registry.hpp>

class PhysicsSystem {
public:
    PhysicsSystem() = default;
    ~PhysicsSystem() = default;

    bool updateX(entt::registry& ecs, float timescale);
    bool updateY(entt::registry& ecs, float timescale);

private:
    void moveToZero(float &value, float amount);

};