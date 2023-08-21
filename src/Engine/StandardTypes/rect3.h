#pragma once

#include <iostream>

namespace strb {
    template <class T>
    struct rect3 final {
        rect3() : x(0), y(0), z(0), w(0), d(0), h(0) {}
        rect3(T x, T y, T z, T w, T d, T h) : x(x), y(y), z(z), w(w), d(d), h(h) {}
        T x, y, z, w, d, h;
       /**
        * width = x axis, depth = y axis, height = z axis
        * world space view in isometric view:
        *      z|
        *       |
        *       |
        *      /\
        *     /  \
        *   x/    \y
       */
    };

    using rect3f = rect3<float>;
    using rect3i = rect3<int>;
}