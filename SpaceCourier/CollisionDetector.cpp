#include "CollisionDetector.h"

#include <algorithm>

bool CollisionDetector::checkCollision(CollisionBox* box, CollisionSphere* sphere)
{
    vec3 difference = sphere->getPosition() - box->getPosition();
    vec3 clamped = clamp(difference, box->getHalfSize() * -1.0f, box->getHalfSize());
    vec3 closestPoint = box->getPosition() + clamped;
    vec3 distance = closestPoint - sphere->getPosition();

    return distance.length() < sphere->getRadius();
}

vec3 CollisionDetector::clamp(vec3 value, vec3 min, vec3 max)
{
    vec3 clamped;
    clamped.x = std::max(min.x, std::min(max.x, value.x));
    clamped.y = std::max(min.y, std::min(max.y, value.y));
    clamped.z = std::max(min.z, std::min(max.z, value.z));

    return clamped;
}
