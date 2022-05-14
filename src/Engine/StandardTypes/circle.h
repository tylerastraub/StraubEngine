#ifndef CIRCLE_H
#define CIRCLE_H

#include "vec2.h"

namespace strb {
    struct circle {
        strb::vec2 pos = {0.f, 0.f};
        float radius = 0.f;
    };
}

#endif