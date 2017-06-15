#pragma once

#include "CollisionBox.h"
#include "CollisionSphere.h"

class CollisionDetector
{
public:
    static bool checkCollision(CollisionBox* box, CollisionSphere* sphere);

private:
    static vec3 clamp(vec3 value, vec3 min, vec3 max);
};
