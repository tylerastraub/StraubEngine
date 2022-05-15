#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "vec2.h"

struct TransformComponent {
    strb::vec2 position;
    strb::vec2 lastPosition;
};

#endif