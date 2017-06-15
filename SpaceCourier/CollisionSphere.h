#pragma once

#include "Vec3.h"

class CollisionSphere
{
public:
    CollisionSphere(float radius, vec3 position);
    ~CollisionSphere();

    float getRadius();
    vec3 getPosition();

private:
    float radius;
    vec3 position;
};
