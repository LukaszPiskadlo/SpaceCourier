#include "Object.h"


Object::Object()
{
}

Object::~Object()
{
}

void Object::setPosition(vec3 position)
{
    this->position = position;
}

void Object::setRotation(vec3 rotation)
{
    this->rotation = rotation;
}

vec3 Object::getPosition()
{
    return position;
}

vec3 Object::getRotation()
{
    return rotation;
}
