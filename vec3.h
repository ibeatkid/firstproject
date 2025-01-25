typedef struct {
    float x, y, z;
} vec3;

// Function prototypes
vec3 vec3_create(float x, float y, float z);
vec3 vec3_add(vec3 v1, vec3 v2);
vec3 vec3_sub(vec3 v1, vec3 v2);
vec3 vec3_scale(vec3 v, float scalar);
float vec3_dot(vec3 v1, vec3 v2);
vec3 vec3_cross(vec3 v1, vec3 v2);
float vec3_length(vec3 v);
vec3 vec3_normalize(vec3 v);

// Function implementations
vec3 vec3_create(float x, float y, float z) {
    return (vec3){x, y, z};
}

vec3 vec3_add(vec3 v1, vec3 v2) {
    return vec3_create(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

vec3 vec3_sub(vec3 v1, vec3 v2) {
    return vec3_create(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

vec3 vec3_scale(vec3 v, float scalar) {
    return vec3_create(v.x * scalar, v.y * scalar, v.z * scalar);
}

float vec3_dot(vec3 v1, vec3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3 vec3_cross(vec3 v1, vec3 v2) {
    return vec3_create(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}

float vec3_length(vec3 v) {
    return sqrtf(vec3_dot(v, v));
}

vec3 vec3_normalize(vec3 v) {
    float length = vec3_length(v);
    return vec3_scale(v, 1.0f / length);
}
