#include "CollisionSphere.h"

CollisionSphere::CollisionSphere(float radius, vec3 position)
    : radius(radius), position(position)
{
}

CollisionSphere::~CollisionSphere()
{
}

float CollisionSphere::getRadius()
{
    return radius;
}

vec3 CollisionSphere::getPosition()
{
    return position;
}
