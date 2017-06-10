#include <ctime>

#include "AsteroidCluster.h"

AsteroidCluster::AsteroidCluster(vec3 position, int size)
{
    this->position = position;
    this->rotation = vec3(0.0f, 0.0f, 0.0f);
    this->scale = vec3(1.0f, 1.0f, 1.0f);

    srand(time(NULL));
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            for (int z = 0; z < size; z++)
            {
                float scaleFactor = (20.0f + rand() % 15) / 100.0f;
                vec3 scale = vec3(scaleFactor, scaleFactor, scaleFactor);

                vec3 pos = vec3(x * 40 + rand() % 15, y * 40 + rand() % 15, z * 40 + rand() % 15);

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
    for each (Asteroid* asteroid in asteroids)
    {
        asteroid->render();
    }
}
