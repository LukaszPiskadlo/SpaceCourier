#pragma once

#include <GL\freeglut.h>

class Model
{
public:
    Model(char* file);
    ~Model();

    GLuint getId();

private:
    GLuint id;

    struct SFace {
        int v[3];
        int n[3];
        int t[3];
    };

    GLuint loadObj(char * file);
};
