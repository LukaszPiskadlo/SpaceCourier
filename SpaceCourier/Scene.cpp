#include <GL\freeglut.h>

#include "Scene.h"
#include "AsteroidCluster.h"

Scene::Scene()
{
}

Scene::~Scene()
{
    delete skybox;
    delete player;
}

void Scene::init()
{
    glEnable(GL_LIGHT0);

    skybox = new Skybox();
    player = new Player();

    objects.push_back(new AsteroidCluster(vec3(-100.0f, -100.0f, -300.0f), 5));
}

void Scene::update()
{
    player->update();

    for each (Object* object in objects)
    {
        object->update();
    }
}

void Scene::render()
{
    // light
    float ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { -1.0f, -1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    player->render();

    skybox->setPosition(player->getPosition());
    skybox->render();

    for each (Object* object in objects)
    {
        object->render();
    }
}
