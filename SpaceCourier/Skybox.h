#pragma once

#include <GL\freeglut.h>

#include "Object.h"

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

    GLuint listId;
};
