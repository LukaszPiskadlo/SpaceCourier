#pragma once

#include "Skybox.h"
#include "Object.h"
#include "Player.h"

class Scene
{
public:
    Player* player;

    Scene();
    ~Scene();

    void init();
    void update();
    void render();

private:
    Skybox* skybox;
};
