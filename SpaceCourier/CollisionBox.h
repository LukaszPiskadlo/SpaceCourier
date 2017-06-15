#pragma once

#include "Vec3.h"

class CollisionBox
{
public:
    CollisionBox(vec3 position, vec3 halfSize);
    ~CollisionBox();

    vec3 getPosition();
    vec3 getHalfSize();

    void setPosition(vec3 position);

private:
    vec3 position;
    vec3 halfSize;
};
