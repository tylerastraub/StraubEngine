#ifndef vec3_H
#define vec3_H

namespace strb {
    struct vec3 {
        vec3() : x(0.f), y(0.f) {}
        vec3(float x, float y, float z) : x(x), y(y), z(z) {}

        vec3 operator+(vec3 const& v) {
            return vec3(x + v.x, y + v.y, z + v.z);
        }

        vec3 operator+=(vec3 const& v) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }
        
        vec3 operator-(vec3 const& v) {
            return vec3(x - v.x, y - v.y, z - v.z);
        }
        
        vec3 operator-=(vec3 const& v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        vec3 operator*(vec3 const& v) {
            return vec3(x * v.x, y * v.y, z * v.z);
        }

        vec3 operator*=(vec3 const& v) {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return *this;
        }

        vec3 operator*(int const& i) {
            return vec3(x * i, y * i, z * i);
        }

        vec3 operator*=(int const& i) {
            x *= i;
            y *= i;
            z *= i;
            return *this;
        }

        vec3 operator*(float const& f) {
            return vec3(x * f, y * f, z * f);
        }

        vec3 operator*=(float const& f) {
            x *= f;
            y *= f;
            z *= f;
            return *this;
        }

        vec3 operator/(vec3 const& v) {
            return vec3(x / v.x, y / v.y, z / v.z);
        }

        vec3 operator/=(vec3 const& v) {
            x /= v.x;
            y /= v.y;
            z /= v.z;
            return *this;
        }

        vec3 operator/(int const& i) {
            return vec3(x / i, y / i, z / i);
        }

        vec3 operator/=(int const& i) {
            x /= i;
            y /= i;
            z /= i;
            return *this;
        }

        vec3 operator/(float const& f) {
            return vec3(x / f, y / f, z / f);
        }

        vec3 operator/=(float const& f) {
            x /= f;
            y /= f;
            z /= f;
            return *this;
        }

        bool operator==(vec3 const& v) {
            return x == v.x && y == v.y && z == v.z;
        }

        bool operator!=(vec3 const& v) {
            return x != v.x || y != v.y || z != v.z;
        }

        float x;
        float y;
        float z;
    };
};

#endif