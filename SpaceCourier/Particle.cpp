#include "Particle.h"

#include <GL\freeglut.h>

Particle::Particle(vec3 position, vec3 velocity, int maxLife)
    : velocity(velocity), maxLife(maxLife)
{
    this->position = position;
    life = 0;
    size = 3.0f;
}

Particle::~Particle()
{
}

void Particle::update()
{
    if (life > maxLife)
    {
        return;
    }

    position = position + velocity;

    life++;
}

void Particle::render()
{
    if (life > maxLife)
    {
        return;
    }

    glPushMatrix();

    glPointSize(size);

    glBegin(GL_POINTS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(position.x, position.y, position.z);
    glEnd();

    glPopMatrix();
}

bool Particle::isAlive()
{
    return life <= maxLife;
}
