#pragma once

#include "vec2.h"

struct PhysicsComponent {
    strb::vec2f velocity = {0.f, 0.f};
    strb::vec2f acceleration = {0.f, 0.f};
    strb::vec2f airAcceleration = {0.f, 0.f};
    strb::vec2f maxVelocity = {0.f, 0.f};

    bool touchingGround = true;
    int offGroundCount = 0; // Number of frames the entity has been off the ground
    float jumpPower = 0.f;
    float frictionCoefficient = 20.f;
    float airFrictionCoefficient = 5.f;
    float gravity = 15.f;
};