#include <vector>
#include <lodepng.h>
#include <iostream>

#include "Texture.h"

Texture::Texture(char* file)
    : Texture(file, GL_LINEAR, GL_LINEAR)
{
}

Texture::Texture(char * file, int magFilter, int minFilter)
{
    id = 0;
    load(file, magFilter, minFilter);
}

Texture::~Texture()
{
}

GLuint Texture::getId()
{
    return id;
}

void Texture::load(char* file, int magFilter, int minFilter)
{
    std::vector<unsigned char> image;
    unsigned int width;
    unsigned int height;

    unsigned int error = lodepng::decode(image, width, height, file);
    if (error)
    {
        std::cout << "Error loading texture " << error << ": " << lodepng_error_text(error) << std::endl;
        return;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);

    if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST)
    {
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
    }
}
