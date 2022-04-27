#ifndef VEC2F_H
#define VEC2F_H

namespace strb {
    struct vec2f {
        vec2f() : x(0.f), y(0.f) {}
        vec2f(float x, float y) : x(x), y(y) {}

        vec2f operator+(vec2f const& v) {
            return vec2f(x + v.x, y + v.y);
        }

        vec2f operator+=(vec2f const& v) {
            x += v.x;
            y += v.y;
            return *this;
        }
        
        vec2f operator-(vec2f const& v) {
            return vec2f(x - v.x, y - v.y);
        }
        
        vec2f operator-=(vec2f const& v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        vec2f operator*(vec2f const& v) {
            return vec2f(x * v.x, y * v.y);
        }

        vec2f operator*=(vec2f const& v) {
            x *= v.x;
            y *= v.y;
            return *this;
        }

        vec2f operator*(int const& i) {
            return vec2f(x * i, y * i);
        }

        vec2f operator*=(int const& i) {
            x *= i;
            y *= i;
            return *this;
        }

        vec2f operator*(float const& i) {
            return vec2f(x * i, y * i);
        }

        vec2f operator*=(float const& i) {
            x *= i;
            y *= i;
            return *this;
        }

        vec2f operator/(vec2f const& v) {
            return vec2f(x / v.x, y / v.y);
        }

        vec2f operator/=(vec2f const& v) {
            x /= v.x;
            y /= v.y;
            return *this;
        }

        vec2f operator/(int const& i) {
            return vec2f(x / i, y / i);
        }

        vec2f operator/=(int const& i) {
            x /= i;
            y /= i;
            return *this;
        }

        vec2f operator/(float const& i) {
            return vec2f(x / i, y / i);
        }

        vec2f operator/=(float const& i) {
            x /= i;
            y /= i;
            return *this;
        }

        bool operator==(vec2f const& v) {
            return x == v.x && y == v.y;
        }

        bool operator!=(vec2f const& v) {
            return x != v.x || y != v.y;
        }

        float x;
        float y;
    };
};

#endif