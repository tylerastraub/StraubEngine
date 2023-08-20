#pragma once

#include "circle.h"

#include <cmath>

class CircleUtils {
public:
    static bool circlesColliding(strb::circle c1, strb::circle c2) {
        return std::hypot(c1.pos.x - c2.pos.x, c1.pos.y - c2.pos.y) < c1.radius + c2.radius;
    }

private:

};