#pragma once

#include "vec2.h"

struct TransformComponent {
    strb::vec2f position;
    strb::vec2f lastPosition;
};