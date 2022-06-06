#ifndef VEC_UTILS_H
#define VEC_UTILS_H

#include "vec2.h"
#include "vec3.h"

class VecUtils {
public:
    static int dotProduct(strb::vec2 v1, strb::vec2 v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    static int dotProduct(strb::vec3 v1, strb::vec3 v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    static bool isZero(strb::vec2 vec) {
        return vec.x == 0 && vec.y == 0;
    }

    static bool isZero(strb::vec3 vec) {
        return vec.x == 0 && vec.y == 0 && vec.z == 0;
    }

private:

};

#endif