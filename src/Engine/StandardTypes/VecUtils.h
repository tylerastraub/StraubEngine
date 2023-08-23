#pragma once

#include "vec2.h"
#include "vec3.h"

class VecUtils {
public:
    template <typename T>
    static int dotProduct(strb::vec2<T> v1, strb::vec2<T> v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    template <typename T>
    static int dotProduct(strb::vec3<T> v1, strb::vec3<T> v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    template <typename T>
    static bool isZero(strb::vec2<T> vec) {
        return vec.x == 0 && vec.y == 0;
    }

    template <typename T>
    static bool isZero(strb::vec3<T> vec) {
        return vec.x == 0 && vec.y == 0 && vec.z == 0;
    }

private:

};