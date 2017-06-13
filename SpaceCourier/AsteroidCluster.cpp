#include "AsteroidCluster.h"

#include <random>

AsteroidCluster::AsteroidCluster(vec3 position, int size)
{
    this->position = position;
    this->rotation = vec3(0.0f, 0.0f, 0.0f);
    this->scale = vec3(1.0f, 1.0f, 1.0f);

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_real_distribution<float> randomScale(20.0f, 35.0f);
    std::uniform_real_distribution<float> randomPosition(40.0f, 55.0f);

    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            for (int z = 0; z < size; z++)
            {
                float scaleFactor = randomScale(generator) / 100.0f;
                vec3 scale = vec3(scaleFactor, scaleFactor, scaleFactor);
                vec3 pos = vec3(x * randomPosition(generator), y * randomPosition(generator), z * randomPosition(generator));

                asteroids.push_back(new Asteroid(pos, scale));
            }
        }
    }
}

AsteroidCluster::~AsteroidCluster()
{
}

void AsteroidCluster::update()
{
    for each (Asteroid* asteroid in asteroids)
    {
        asteroid->update();
    }
}

void AsteroidCluster::render()
{
    glPushMatrix();

    glTranslatef(position.x, position.y, position.z);

    for each (Asteroid* asteroid in asteroids)
    {
        asteroid->render();
    }

    glPopMatrix();
}
