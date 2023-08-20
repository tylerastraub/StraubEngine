#pragma once

#include <iostream>

namespace strb {
    template <class T>
    struct vec3 final {
        vec3() : x(0.f), y(0.f) {}
        vec3(T x, T y, T z) : x(x), y(y), z(z) {}
        T x, y, z;
        
    };

    using vec3f = vec3<float>;
    using vec3i = vec3<int>;

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const vec3<T>& vec) {
        return os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ") ";
    }

    template <typename T, typename U>
    vec3<T> operator+(vec3<T> const& l, vec3<U> const& r) {
        return vec3<T>(l.x + r.x, l.y + r.y, l.z + r.z);
    }

    template <typename T, typename U>
    vec3<T> operator+=(vec3<T> const& l, vec3<U> const& r) {
        l.x += r.x;
        l.y += r.y;
        l.z += r.z;
        return l;
    }
    
    template <typename T, typename U>
    vec3<T> operator-(vec3<T> const& l, vec3<U> const& r) {
        return vec3<T>(l.x - r.x, l.y - r.y, l.z - r.z);
    }
    
    template <typename T, typename U>
    vec3<T> operator-=(vec3<T> const& l, vec3<U> const& r) {
        l.x -= r.x;
        l.y -= r.y;
        l.z -= r.z;
        return l;
    }

    template <typename T, typename U>
    vec3<T> operator*(vec3<T> const& l, vec3<U> const& r) {
        return vec3<T>(l.x * r.x, l.y * r.y, l.z * r.z);
    }

    template <typename T, typename U>
    vec3<T> operator*=(vec3<T> const& l, vec3<U> const& r) {
        l.x *= r.x;
        l.y *= r.y;
        l.z *= r.z;
        return l;
    }

    template <typename T, typename U>
    vec3<T> operator*(vec3<T> const& l, U const& f) {
        return vec3<T>(l.x * f, l.y * f, l.z * f);
    }

    template <typename T, typename U>
    vec3<T> operator*=(vec3<T> const& l, U const& f) {
        l.x *= f;
        l.y *= f;
        l.z *= f;
        return l;
    }

    template <typename T, typename U>
    vec3<T> operator/(vec3<T> const& l, vec3<U> const& r) {
        return vec3<T>(l.x / r.x, l.y / r.y, l.z / r.z);
    }

    template <typename T, typename U>
    vec3<T> operator/=(vec3<T> const& l, vec3<U> const& r) {
        l.x /= r.x;
        l.y /= r.y;
        l.z /= r.z;
        return l;
    }

    template <typename T, typename U>
    vec3<T> operator/(vec3<T> const& l, U const& f) {
        return vec3<T>(l.x / f, l.y / f, l.z / f);
    }

    template <typename T, typename U>
    vec3<T> operator/=(vec3<T> const& l, U const& f) {
        l.x /= f;
        l.y /= f;
        l.z /= f;
        return l;
    }

    template <typename T, typename U>
    bool operator==(vec3<T> const& l, vec3<U> const& r) {
        return l.x == r.x && l.y == r.y && l.z == r.z;
    }

    template <typename T, typename U>
    bool operator!=(vec3<T> const& l, vec3<U> const& r) {
        return l.x != r.x || l.y != r.y || l.z != r.z;
    }
};