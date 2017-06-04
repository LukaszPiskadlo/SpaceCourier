#pragma once

#include "Vec3.h"

class Object
{
public:
    Object();
    ~Object();

    virtual void update() = 0;
    virtual void render() = 0;

    void setPosition(vec3 position);
    void setRotation(vec3 rotation);

    vec3 getPosition();
    vec3 getRotation();

protected:
    vec3 position;
    vec3 rotation;
};
