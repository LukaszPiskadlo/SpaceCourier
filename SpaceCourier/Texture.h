#pragma once

#include <GL\freeglut.h>

class Texture
{
public:
    Texture(char* file);
    Texture(char* file, int magFilter, int minFilter);
    ~Texture();

    GLuint getId();

private:
    GLuint id;

    void load(char* file, int magFilter, int minFilter);
};
