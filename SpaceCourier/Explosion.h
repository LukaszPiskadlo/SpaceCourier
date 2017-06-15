#pragma once

#include "Object.h"
#include "Particle.h"
#include "Vec3.h"

#include <vector>

class Explosion :
    public Object
{
public:
    Explosion(vec3 position);
    ~Explosion();

    virtual void update() override;
    virtual void render() override;

private:
    std::vector<Particle*> particles;
    int maxParticles;
};
