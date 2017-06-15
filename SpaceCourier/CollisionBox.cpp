#include "CollisionBox.h"

CollisionBox::CollisionBox(vec3 position, vec3 halfSize)
    : position(position), halfSize(halfSize)
{
}

CollisionBox::~CollisionBox()
{
}

vec3 CollisionBox::getPosition()
{
    return position;
}

vec3 CollisionBox::getHalfSize()
{
    return halfSize;
}

void CollisionBox::setPosition(vec3 position)
{
    this->position = position;
}
