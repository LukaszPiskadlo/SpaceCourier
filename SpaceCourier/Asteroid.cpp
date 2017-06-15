#include "Asteroid.h"

Model* Asteroid::model = nullptr;
Texture* Asteroid::texture = nullptr;

Asteroid::Asteroid(vec3 position, vec3 scale)
{
    this->position = position;
    this->scale = scale;
    this->rotation = vec3(0.0f, 0.0f, 0.0f);

    isVisible = true;

    if (model == nullptr)
    {
        model = new Model("Resources\\asteroid.obj");
    }

    if (texture == nullptr)
    {
        texture = new Texture("Resources\\asteroid_rock02.png", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
    }

    vec3 collisionSpherePos(position.x, position.y + 4.0f, position.z);
    collisionSphere = new CollisionSphere(50.0f * scale.x, collisionSpherePos);
}

Asteroid::~Asteroid()
{
    delete model;
    delete texture;
    delete collisionSphere;
}

void Asteroid::update()
{
}

void Asteroid::render()
{
    if (!isVisible)
    {
        return;
    }

    glPushMatrix();

    float materialAmbDiff[] = { 1.0f, 1.0f, 1.0f };
    float materialSpecular[] = { 0.0f, 0.0f, 0.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialAmbDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

    glTranslatef(position.x, position.y, position.z);
    glScalef(scale.x, scale.y, scale.z);

    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, texture->getId());
    glCallList(model->getId());

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    // (debug) show collisions mesh
    /*glPushMatrix();

    vec3 cpos = collisionSphere->getPosition();
    glTranslatef(cpos.x, cpos.y, cpos.z);
    glutWireSphere(collisionSphere->getRadius(), 8, 8);

    glPopMatrix();*/
}

CollisionSphere* Asteroid::getCollisionSphere()
{
    return collisionSphere;
}

void Asteroid::setVisibility(bool isVisible)
{
}
