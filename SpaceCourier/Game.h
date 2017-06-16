#pragma once

#include "Scene.h"
#include "Menu.h"

class Game
{
public:
    Game();
    ~Game();

    void init(int* argc, char** argv);

private:
    static const int updateTime;
    static const char* gameName;
    static bool keystate[255];

    const int windowWidth;
    const int windowHeight;
    const int windowPosX;
    const int windowPosY;

    static Scene* scene;
    static Menu* menu;

    static void onRender();
    static void onReshape(int width, int height);
    static void onKeyPress(unsigned char key, int x, int y);
    static void onKeyDown(unsigned char key, int x, int y);
    static void onKeyUp(unsigned char key, int x, int y);
    static void onMouseMove(int x, int y);
    static void onTimer(int id);
};
