#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "vec2f.h"

struct TransformComponent {
    strb::vec2f position;
    strb::vec2f lastPosition;
};

#endif