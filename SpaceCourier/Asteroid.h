#pragma once

#include "Object.h"
#include "Model.h"
#include "Texture.h"

class Asteroid :
    public Object
{
public:
    Asteroid(vec3 position, vec3 scale);
    ~Asteroid();

    void update();
    void render();

private:
    Model* model;
    Texture* texture;
};
