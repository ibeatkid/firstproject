#ifndef VEC3_H
#define VEC3_H
#include <cmath>
#include <stdio.h>

typedef struct {
    float x, y, z;
} vec3;

vec3 vec3create(float x, float y, float z) {
    return (vec3){x, y, z};
}

vec3 vec3add(vec3 v1, vec3 v2) {
    return vec3create(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

vec3 vec3sub(vec3 v1, vec3 v2) {
    return vec3create(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

vec3 vec3scale(vec3 v, float scalar) {
    return vec3create(v.x * scalar, v.y * scalar, v.z * scalar);
}

float vec3dot(vec3 v1, vec3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3 vec3cross(vec3 v1, vec3 v2) {
    return vec3create(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}

float vec3length(vec3 v) {
    return sqrtf(vec3dot(v, v));
}

vec3 vec3normalize(vec3 v) {
    float length = vec3length(v);
    if (length == 0.0f) {
        fprintf(stderr, "Warning: Attempting to normalize a zero-length vector.\n");
        return vec3create(0.0f, 0.0f, 0.0f);
    }
    return vec3scale(v, 1.0f / length);
}
#endif
