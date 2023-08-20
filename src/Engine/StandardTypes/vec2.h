#pragma once

#include <iostream>

namespace strb {
    template <class T>
    struct vec2 final {
        vec2() : x(0), y(0) {}
        vec2(T x, T y) : x(x), y(y) {}
        T x, y;
    };

    using vec2f = vec2<float>;
    using vec2i = vec2<int>;
    
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const vec2<T>& vec) {
        return os << "(" << vec.x << ", " << vec.y << ") ";
    }

    template <typename T, typename U>
    vec2<T> operator + (const vec2<T>& l, const vec2<U>& r) {
        return { l.x + r.x, l.y + r.y };
    }

    template <typename T, typename U>
    vec2<T>& operator += (vec2<T>& l, const vec2<U>& r) {
        l.x += r.x;
        l.y += r.y;
        return l;
    }

    template <typename T, typename U>
    vec2<T> operator - (const vec2<T>& l, const vec2<U>& r) {
        return { l.x - r.x, l.y - r.y };
    }

    template <typename T, typename U>
    vec2<T>& operator -= (vec2<T>& l, const vec2<U>& r) {
        l.x -= r.x;
        l.y -= r.y;
        return l;
    }

    template <typename T, typename U>
    vec2<T> operator * (const vec2<T>& l, const vec2<U>& r) {
        return { l.x * r.x, l.y * r.y };
    }

    template <typename T, typename U>
    vec2<T>& operator *= (vec2<T>& l, const vec2<U>& r) {
        l.x *= r.x;
        l.y *= r.y;
        return l;
    }

    template <typename T, typename U>
    vec2<T> operator * (const vec2<T>& l, U r) {
        return { l.x * r, l.y * r };
    }

    template <typename T, typename U>
    vec2<T>& operator *= (vec2<T>& l, U r) {
        l.x *= r;
        l.y *= r;
        return l;
    }

    template <typename T, typename U>
    vec2<T> operator / (const vec2<T>& l, const vec2<U>& r) {
        return { l.x / r.x, l.y / r.y };
    }

    template <typename T, typename U>
    vec2<T>& operator /= (vec2<T>& l, const vec2<U>& r) {
        l.x /= r.x;
        l.y /= r.y;
        return l;
    }

    template <typename T, typename U>
    vec2<T> operator / (const vec2<T>& l, U r) {
        return { l.x / r, l.y / r };
    }

    template <typename T, typename U>
    vec2<T>& operator /= (vec2<T>& l, U r) {
        l.x /= r;
        l.y /= r;
        return l;
    }

    template <typename T, typename U>
    bool operator == (vec2<T>& l, vec2<U>& r) {
        return l.x == r.x && l.y == r.y;
    }

    template <typename T, typename U>
    bool operator != (vec2<T>& l, vec2<U>& r) {
        return l.x != r.x || l.y != r.y;
    }
};