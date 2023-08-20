#pragma once

#include "vec2.h"
#include "rect2.h"

struct CollisionComponent {
    strb::vec2i collisionRectOffset = {0, 0}; // the collision rect's offset from the entity's transform position
    strb::rect2i collisionRect = {0, 0, 0, 0};

    bool collidingLeft = false;
    bool collidingRight = false;
    bool collidingUp = false;
    bool collidingDown = false;
};