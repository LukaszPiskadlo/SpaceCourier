#pragma once

#include "Object.h"
#include <vector>

#include "Asteroid.h"

class AsteroidCluster :
    public Object
{
public:
    AsteroidCluster(vec3 position, int xDim, int yDim, int zDim);
    ~AsteroidCluster();

    virtual void update() override;
    virtual void render() override;

private:
    std::vector<Asteroid*> asteroids;
};
