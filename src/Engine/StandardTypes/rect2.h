#pragma once

#include <iostream>

namespace strb {
    template <class T>
    struct rect2 final {
        rect2() : x(0), y(0), w(0), h(0) {}
        rect2(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}
        T x, y, w, h;
    };

    using rect2f = rect2<float>;
    using rect2i = rect2<int>;
}