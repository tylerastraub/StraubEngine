#ifndef VEC_UTILS_H
#define VEC_UTILS_H

#include "vec2.h"

class VecUtils {
public:
    static int dotProduct(strb::vec2 v1, strb::vec2 v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    static bool isZero(strb::vec2 vec) {
        return vec.x == 0 && vec.y == 0;
    }

    static bool isZero(strb::vec2 vec) {
        return vec.x == 0.f && vec.y == 0.f;
    }

private:

};

#endif