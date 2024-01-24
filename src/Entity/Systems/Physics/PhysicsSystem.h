#pragma once

#include <entt/entity/registry.hpp>

class PhysicsSystem {
public:
    PhysicsSystem() = default;
    ~PhysicsSystem() = default;

    void updateX(entt::registry& ecs, float timescale);
    void updateY(entt::registry& ecs, float timescale);

private:
    void moveToZero(float &value, float amount);

};