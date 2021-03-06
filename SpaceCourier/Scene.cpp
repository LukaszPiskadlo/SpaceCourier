#include <GL\freeglut.h>

#include "Scene.h"
#include "Settings.h"
#include "CollisionDetector.h"
#include "Explosion.h"

Scene::Scene()
{
}

Scene::~Scene()
{
    delete skybox;
    delete player;
    delete asteroidCluster;
}

void Scene::init()
{
    glEnable(GL_LIGHT0);

    skybox = new Skybox();
    player = new Player();

    asteroidCluster = new AsteroidCluster(vec3(-275.0f, -275.0f, -1200.0f), 10, 10, 20);

    float xMin = asteroidCluster->getEdges().at(0).x;
    float xMax = asteroidCluster->getEdges().at(1).x;
    float yMin = asteroidCluster->getEdges().at(0).y;
    float yMax = asteroidCluster->getEdges().at(2).y;
    player->setLimits(xMin, xMax, yMin, yMax);

    glEnable(GL_FOG);
    float fogColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_START, 200.0f);
    glFogf(GL_FOG_END, 300.0f);
}

void Scene::update()
{
    player->update();

    for each (Asteroid* asteroid in asteroidCluster->getAsteroids())
    {
        vec3 distance = player->getPosition() - asteroid->getPosition();
        if (distance.length() < 40.0f)
        {
            for each (CollisionBox* box in player->getCollisionBoxes())
            {
                bool collide = CollisionDetector::checkCollision(box, asteroid->getCollisionSphere());

                if (collide && player->isAlive())
                {
                    player->setDead(true);
                    objects.push_back(new Explosion(player->getPosition()));
                }
            }
        }

        if (distance.length() > 200.0f || asteroid->getPosition().z > player->getPosition().z)
        {
            asteroid->setVisibility(false);
        }
        else
        {
            asteroid->setVisibility(true);
        }
    }

    for each (Object* object in objects)
    {
        object->update();
    }
}

void Scene::render()
{
    float ambient[] = { 0.86f, 0.86f, 0.98f, 1.0f };
    float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { -1.0f, -1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    player->render();

    glDisable(GL_FOG);
    skybox->setPosition(player->getPosition());
    skybox->render();
    glEnable(GL_FOG);

    asteroidCluster->render();

    for each (Object* object in objects)
    {
        object->render();
    }
}

void Scene::nextMission(int mission)
{
    float zMax = asteroidCluster->getEdges().at(3).z;
    if (player->getPosition().z > zMax)
    {
        return;
    }

    player->moveStop();

    switch (mission)
    {
    case NORMAL:
        asteroidCluster = new AsteroidCluster(vec3(-275.0f, -275.0f, -1200.0f), 10, 10, 20);
        break;
    case LONG_NORMAL:
        asteroidCluster = new AsteroidCluster(vec3(-160.0f, -160.0f, -1800.0f), 7, 7, 30);
        break;
    case FAST:
        asteroidCluster = new AsteroidCluster(vec3(-275.0f, -275.0f, -1200.0f), 10, 10, 20);
        player->setSpeed(DEFAULT_SPEED + 10.0f);
        break;
    case LONG_FAST:
        asteroidCluster = new AsteroidCluster(vec3(-160.0f, -160.0f, -1800.0f), 7, 7, 30);
        player->setSpeed(DEFAULT_SPEED + 10.0f);
        break;
    default:
        break;
    }

    player->setPosition(vec3(0.0f, 0.0f, 0.0f));

    float xMin = asteroidCluster->getEdges().at(0).x;
    float xMax = asteroidCluster->getEdges().at(1).x;
    float yMin = asteroidCluster->getEdges().at(0).y;
    float yMax = asteroidCluster->getEdges().at(2).y;
    player->setLimits(xMin, xMax, yMin, yMax);
}
