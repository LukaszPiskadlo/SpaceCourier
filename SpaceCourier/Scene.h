#pragma once

#include "Skybox.h"
#include "Object.h"
#include "Player.h"

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

private:
    Skybox* skybox;
    std::vector<Object*> objects;
};
