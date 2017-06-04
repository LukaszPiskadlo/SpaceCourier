#pragma once

#include <GL\freeglut.h>

#include "Object.h"
#include "Texture.h"

class Skybox :
    public Object
{
public:
    Skybox();
    ~Skybox();

    void update();
    void render();

private:
    static const int listCount;

    GLuint listId[6];
    Texture* spaceBoxUp;
    Texture* spaceBoxDown;
    Texture* spaceBoxFront;
    Texture* spaceBoxBack;
    Texture* spaceBoxLeft;
    Texture* spaceboxRight;

    enum sideIds
    {
        UP,
        FRONT,
        DOWN,
        BACK,
        LEFT,
        RIGHT
    };
};
