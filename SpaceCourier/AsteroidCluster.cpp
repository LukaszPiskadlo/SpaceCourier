#include "AsteroidCluster.h"
#include "RandomNumber.h"

AsteroidCluster::AsteroidCluster(vec3 position, int xDim, int yDim, int zDim)
{
    this->position = position;
    this->rotation = vec3(0.0f, 0.0f, 0.0f);
    this->scale = vec3(1.0f, 1.0f, 1.0f);

    RandomNumber<float>* randomScale = new RandomNumber<float>(30.0f, 45.0f);
    RandomNumber<float>* randomPosition = new RandomNumber<float>(40.0f, 55.0f);

    for (int x = 0; x < xDim; x++)
    {
        for (int y = 0; y < yDim; y++)
        {
            for (int z = 0; z < zDim; z++)
            {
                float scaleFactor = randomScale->generate() / 100.0f;
                vec3 scale = vec3(scaleFactor, scaleFactor, scaleFactor);
                vec3 pos = vec3(x * randomPosition->generate(), y * randomPosition->generate(), z * randomPosition->generate());

                asteroids.push_back(new Asteroid(pos, scale));
            }
        }
    }

    delete randomScale;
    delete randomPosition;
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
