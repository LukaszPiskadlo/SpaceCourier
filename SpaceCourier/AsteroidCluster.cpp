#include "AsteroidCluster.h"
#include "RandomNumber.h"

AsteroidCluster::AsteroidCluster(vec3 position, int xDim, int yDim, int zDim)
{
    this->position = position;
    this->rotation = vec3(0.0f, 0.0f, 0.0f);
    this->scale = vec3(1.0f, 1.0f, 1.0f);

    edges = std::vector<vec3>(4);

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

                pos = position + pos;

                asteroids.push_back(new Asteroid(pos, scale));

                if (x == 0 && y == 0 && z == 0)
                {
                    edges[0] = pos;
                }
                else if (x == xDim - 1 && y == 0 && z == 0)
                {
                    edges[1] = pos;
                }
                else if (x == 0 && y == yDim - 1 && z == 0)
                {
                    edges[2] = pos;
                }
                else if (x == 0 && y == 0 && z == zDim - 1)
                {
                    edges[3] = pos;
                }
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

    for each (Asteroid* asteroid in asteroids)
    {
        asteroid->render();
    }

    glPopMatrix();
}

std::vector<Asteroid*> AsteroidCluster::getAsteroids()
{
    return asteroids;
}

std::vector<vec3> AsteroidCluster::getEdges()
{
    return edges;
}
