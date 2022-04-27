#ifndef RIGID_BODY_COMPONENT_H
#define RIGID_BODY_COMPONENT_H

#include "vec2f.h"

struct RigidBodyComponent {
    strb::vec2f velocity;
    strb::vec2f acceleration;
    float maxVelocity;
};

#endif