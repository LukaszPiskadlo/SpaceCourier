#include "Explosion.h"
#include "RandomNumber.h"

#include <GL\freeglut.h>

Explosion::Explosion(vec3 position)
{
    this->position = position;
    maxParticles = 200;

    RandomNumber<float>* randomVelocity = new RandomNumber<float>(-0.7f, 0.7f);
    RandomNumber<float>* randomLife = new RandomNumber<float>(10.0f, 15.0f);

    for (int i = 0; i < maxParticles; i++)
    {
        vec3 velocity(randomVelocity->generate(), randomVelocity->generate(), randomVelocity->generate());
        particles.push_back(new Particle(position, velocity, (int)randomLife->generate()));
    }

    glEnable(GL_LIGHT2);
}

Explosion::~Explosion()
{
    glDisable(GL_LIGHT2);
}

void Explosion::update()
{
    for each (Particle* particle in particles)
    {
        particle->update();
    }
}

void Explosion::render()
{
    float ambient[] = { 1.0f, 0.5f, 0.0f, 1.0f };
    float diffuse[] = { 1.0f, 0.5f, 0.0f, 1.0f };
    float specular[] = { 1.0f, 0.5f, 0.0f, 1.0f };
    float lightPos[] = { position.x, position.y, position.z };
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos);
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.005f);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.003f);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.001f);

    for each (Particle* particle in particles)
    {
        particle->render();
    }
}
