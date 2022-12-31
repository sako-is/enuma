#pragma once

#include "defines.h"

typedef enum Type {
    i8, i16, i32, i64, u8, u16, u32, u64
} Type;

typedef struct Vec2 {
    union { Type x, r, u, s; };
    union { Type y, g, v, t; };
} Vec2;

typedef struct Vec3 {
    union { Type x, r, u, s; };
    union { Type y, g, v, t; };
    union { Type z, b, w, p; };
} Vec3;

typedef struct Vec4 {
    union { Type x, r, s; };
    union { Type y, g, t; };
    union { Type z, b, p; };
    union { Type w, a, q; };
} Vec4;

ENMAPI Vec2 vec2(Type type, void* x, void* y);
ENMAPI Vec3 vec3(Type type, void* x, void* y, void* z);
ENMAPI Vec4 vec4(Type type, void* x, void* y, void* z, void* w);