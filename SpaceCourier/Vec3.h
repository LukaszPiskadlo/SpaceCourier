#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

struct vec3 {

    float x, y, z;

    vec3() {
        x = y = z = 0.0f;
    }

    vec3(float nx, float ny, float nz) {
        x = nx;
        y = ny;
        z = nz;
    }

    vec3(float nxyz) {
        x = y = z = nxyz;
    }

    void set(float nxyz) {
        x = y = z = nxyz;
    }

    void set(float nx, float ny, float nz) {
        x = nx;
        y = ny;
        z = nz;
    }

    void set(vec3 v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    vec3 operator=(const vec3 v) {
        set(v.x, v.y, v.z);
        return *this;
    }

    vec3 operator-(const vec3 v) {
        return vec3(x - v.x, y - v.y, z - v.z);
    }

    vec3 operator+(const vec3 v) {
        return vec3(x + v.x, y + v.y, z + v.z);
    }

    vec3 operator*(const float f) {
        return vec3(x * f, y * f, z * f);
    }

    bool operator>(vec3 v) {
        return (x > v.x && y > v.y && z > v.z);
    }

    bool operator>=(vec3 v) {
        return (x >= v.x && y >= v.y && z >= v.z);
    }

    bool operator<(vec3 v) {
        return (x < v.x && y < v.y && z < v.z);
    }

    bool operator<=(vec3 v) {
        return (x <= v.x && y <= v.y && z <= v.z);
    }

    bool operator==(vec3 v) {
        return (x == v.x && y == v.y && z == v.z);
    }

    float length() {
        return sqrt(x * x + y * y + z * z);
    }

    float length2() {
        return x * x + y * y + z * z;
    }

    void normalize() {
        float d = length();
        x /= d;
        y /= d;
        z /= d;
    }

    void setLength(float l) {
        normalize();
        x *= l;
        y *= l;
        z *= l;
    }

    void rotate(vec3 r) {
        r = r * (M_PI / 180.0);

        float nx = x * cos(r.y) * cos(r.z) + y * (-cos(r.x) * sin(r.z) + sin(r.x)
            * sin(r.y) * cos(r.z)) + z * (sin(r.x) * sin(r.z) + cos(r.x) * sin(r.y) * cos(r.z));
        float ny = x * cos(r.y) * sin(r.z) + y * (cos(r.x) * cos(r.z) + sin(r.x)
            * sin(r.y) * sin(r.z)) + z * (-sin(r.x) * cos(r.z) + cos(r.x) * sin(r.y) * sin(r.z));
        float nz = -x * sin(r.y) + y * sin(r.x) * cos(r.y) + z * cos(r.x) * cos(r.y);

        x = nx;
        y = ny;
        z = nz;
    }

    void scale(float s) {
        x *= s;
        y *= s;
        z *= s;
    }

    void scale(float sx, float sy, float sz) {
        x *= sx;
        y *= sy;
        z *= sz;
    }

    void scale(vec3 s) {
        x *= s.x;
        y *= s.y;
        z *= s.z;
    }

    float dot(vec3 b) {
        return x * b.x + y * b.y + z * b.z;
    }

    static void cross(vec3 a, vec3 b, vec3 &c) {
        c.x = a.y * b.z - a.z * b.y;
        c.y = a.z * b.x - a.x * b.z;
        c.z = a.x * b.y - a.y * b.x;
    }

};
