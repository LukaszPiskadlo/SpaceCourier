#pragma once

#include "Object.h"
#include "Vec3.h"

class Particle :
    public Object
{
public:
    Particle(vec3 position, vec3 velocity, int maxLife);
    ~Particle();

    virtual void update() override;
    virtual void render() override;

    bool isAlive();

private:
    int maxLife;
    int life;
    vec3 velocity;
    float size;
};
