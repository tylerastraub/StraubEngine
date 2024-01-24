#pragma once

#include "rect2.h"
#include "rect3.h"

class RectUtils {
public:
    RectUtils() = default;
    ~RectUtils() = default;

    template <typename T>
    static bool isIntersecting (strb::rect2<T> rect1, strb::rect2<T> rect2) {
        return (rect1.x < rect2.x + rect2.w &&
                rect1.x + rect1.w > rect2.x &&
                rect1.y < rect2.y + rect2.h &&
                rect1.y + rect1.h > rect2.y);
    }

    template <typename T>
    static bool isIntersecting (strb::rect3<T> rect1, strb::rect3<T> rect2) {
        return (rect1.x < rect2.x + rect2.w &&
                rect1.x + rect1.w > rect2.x &&
                rect1.y < rect2.y + rect2.d &&
                rect1.y + rect1.d > rect2.y &&
                rect1.z < rect2.z + rect2.h &&
                rect1.z + rect1.h > rect2.z);
    }

private:

};