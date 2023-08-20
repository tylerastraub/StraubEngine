#pragma once

#include "vec2.h"
#include "vec3.h"

class VecUtils {
public:
    static int dotProduct(strb::vec2f v1, strb::vec2f v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    static int dotProduct(strb::vec3 v1, strb::vec3 v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    static bool isZero(strb::vec2f vec) {
        return vec.x == 0.f && vec.y == 0.f;
    }

    static bool isZero(strb::vec2i vec) {
        return vec.x == 0 && vec.y == 0;
    }

    static bool isZero(strb::vec3 vec) {
        return vec.x == 0 && vec.y == 0 && vec.z == 0;
    }

private:

};