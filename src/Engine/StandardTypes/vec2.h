#ifndef VEC2_H
#define VEC2_H

namespace strb {
    struct vec2 {
        vec2() : x(0), y(0) {}
        vec2(int x, int y) : x(x), y(y) {}

        vec2 operator+(vec2 const& v) {
            return vec2(x + v.x, y + v.y);
        }

        vec2 operator+=(vec2 const& v) {
            x += v.x;
            y += v.y;
            return *this;
        }
        
        vec2 operator-(vec2 const& v) {
            return vec2(x - v.x, y - v.y);
        }
        
        vec2 operator-=(vec2 const& v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        vec2 operator*(vec2 const& v) {
            return vec2(x * v.x, y * v.y);
        }

        vec2 operator*=(vec2 const& v) {
            x *= v.x;
            y *= v.y;
            return *this;
        }

        vec2 operator*(int const& i) {
            return vec2(x * i, y * i);
        }

        vec2 operator*=(int const& i) {
            x *= i;
            y *= i;
            return *this;
        }

        vec2 operator*(float const& i) {
            return vec2(x * i, y * i);
        }

        vec2 operator*=(float const& i) {
            x *= i;
            y *= i;
            return *this;
        }

        vec2 operator/(vec2 const& v) {
            return vec2(x / v.x, y / v.y);
        }

        vec2 operator/=(vec2 const& v) {
            x /= v.x;
            y /= v.y;
            return *this;
        }

        vec2 operator/(int const& i) {
            return vec2(x / i, y / i);
        }

        vec2 operator/=(int const& i) {
            x /= i;
            y /= i;
            return *this;
        }

        vec2 operator/(float const& i) {
            return vec2(x / i, y / i);
        }

        vec2 operator/=(float const& i) {
            x /= i;
            y /= i;
            return *this;
        }

        bool operator==(vec2 const& v) {
            return x == v.x && y == v.y;
        }

        bool operator!=(vec2 const& v) {
            return x != v.x || y != v.y;
        }

        int x;
        int y;
    };
};

#endif