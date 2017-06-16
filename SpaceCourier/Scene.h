#pragma once

#include "Skybox.h"
#include "Object.h"
#include "Player.h"
#include "AsteroidCluster.h"

#include <vector>

class Scene
{
public:
    Player* player;

    Scene();
    ~Scene();

    void init();
    void update();
    void render();

    void nextMission(int mission);

private:
    Skybox* skybox;
    AsteroidCluster* asteroidCluster;
    std::vector<Object*> objects;
};
