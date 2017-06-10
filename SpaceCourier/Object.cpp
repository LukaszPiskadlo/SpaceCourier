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

void Object::setScale(vec3 scale)
{
    this->scale = scale;
}

vec3 Object::getPosition()
{
    return position;
}

vec3 Object::getRotation()
{
    return rotation;
}

vec3 Object::getScale()
{
    return scale;
}
