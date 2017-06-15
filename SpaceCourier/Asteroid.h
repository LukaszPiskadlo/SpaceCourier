#pragma once

#include "Object.h"
#include "Model.h"
#include "Texture.h"
#include "CollisionSphere.h"

class Asteroid :
    public Object
{
public:
    Asteroid(vec3 position, vec3 scale);
    ~Asteroid();

    virtual void update() override;
    virtual void render() override;

    CollisionSphere* getCollisionSphere();
    void setVisibility(bool isVisible);

private:
    static Model* model;
    static Texture* texture;

    CollisionSphere* collisionSphere;
    bool isVisible;
};
