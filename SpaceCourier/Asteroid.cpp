#include "Asteroid.h"

Model* Asteroid::model = nullptr;
Texture* Asteroid::texture = nullptr;

Asteroid::Asteroid(vec3 position, vec3 scale)
{
    this->position = position;
    this->scale = scale;
    this->rotation = vec3(0.0f, 0.0f, 0.0f);

    if (model == nullptr)
    {
        model = new Model("Resources\\asteroid.obj");
    }

    if (texture == nullptr)
    {
        texture = new Texture("Resources\\asteroid_rock02.png", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
    }
}

Asteroid::~Asteroid()
{
    delete model;
    delete texture;
}

void Asteroid::update()
{
}

void Asteroid::render()
{
    glPushMatrix();

    float mA[] = { 1.0f, 1.0f, 1.0f };
    float mS[] = { 0.0f, 0.0f, 0.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mA);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mS);

    glTranslatef(position.x, position.y, position.z);
    glScalef(scale.x, scale.y, scale.z);

    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, texture->getId());
    glCallList(model->getId());

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
