#pragma once
#include "vec3.h"

// struct vertex
// {
//     vec3 pos;
//     vec2 tex;
//     vec3 norm;
// }

struct vec2
{
    float x,y;
};

struct triangle
{
        vec3 a, b, c;
        vec2 d1, d2;
        vec3 n1, n2, n3;
        
};

struct b_b
{
    vec3 min_corner;
    vec3 max_corner;
    vec3 center() const {return (max_corner + min_corner) * 0.5f;}
};

struct MaybeTwoIntersections
{
    float tMin, tMax;
};

MaybeTwoIntersections const None = {.tMin = 0.f, .tMax = -1.f};

inline bool happened(MaybeTwoIntersections const i)
{
    return i.tMin <= i.tMax;
}

struct Ray
{ 
    vec3 origin;
    vec3 direction;
    vec3 point(float const t) const {return origin + direction * t;}
};

struct RayTriangleIntersection
{
    float t, p, q;
};

inline MaybeTwoIntersections rayboxIntersection(Ray const &ray, b_b const &box)
{
    vec3 const a = (box.min_corner - ray.origin) / ray.direction;
    vec3 const b = (box.max_corner - ray.origin) / ray.direction;
    auto const min = [](float const x, float const y) {return x < y ? x : y;};
    auto const max = [](float const x, float const y) {return x < y ? y : x;};
    vec3 const tMin =
    {
        min(a.x, b.x),
        min(a.y, b.y),
        min(a.z, b.z),
    };
    vec3 const tMax =
    {
        max(a.x, b.x),
        max(a.y, b.y),
        max(a.z, b.z),
    };
    return
    {
        max(max(tMin.x, tMin.y), tMin.z),
        min(min(tMax.x, tMax.y), tMax.z),
    };
}

inline RayTriangleIntersection rayTriangleIntersection(Ray const &ray, triangle const &Triangle)
{
    vec3 const a = Triangle.b - Triangle.a;
    vec3 const b = Triangle.c - Triangle.a;
    vec3 const c = ray.origin - Triangle.a;
    vec3 const d = ray.direction;
    float const det0 = dot(-d, cross(a, b));
    float const det1 = dot( c, cross(a, b));
    float const det2 = dot(-d, cross(c, b));
    float const det3 = dot(-d, cross(a, c));
    return 
    {
        .t = det1 / det0,
        .p = det2 / det0,
        .q = det3 / det0,
    };
}

inline bool happened(RayTriangleIntersection const &i)
{
    return i.p >= 0.f
        && i.q >= 0.f
        && i.p + i.q <= 1.f;
}