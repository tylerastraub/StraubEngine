#pragma once

#include "vec2.h"
#include "rect2.h"

struct CollisionComponent {
    strb::rect2f collisionRect = {0, 0, 0, 0};
    strb::vec2f collisionRectOffset = {0, 0}; // the collision rect's offset from the entity's transform position

    bool collidingLeft = false;
    bool collidingRight = false;
    bool collidingUp = false;
    bool collidingDown = false;
};