#include <GL\freeglut.h>

#include "Scene.h"

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
    player->render();

    // light
    float l0_amb[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float l0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float l0_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float l0_pos[] = { -1.0f, 0.2f, 0.5f, 0.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
    glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);

    skybox->setPosition(player->getPosition());
    skybox->render();

    for each (Object* object in objects)
    {
        object->render();
    }
}
