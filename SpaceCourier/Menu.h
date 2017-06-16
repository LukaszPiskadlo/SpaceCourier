#pragma once

#include "Settings.h"

#include <string>

class Menu
{
public:
    Menu();
    ~Menu();

    void startGame();
    void gameOver();
    MissionDifficulty nextMission();

    void render();

private:
    void displayText(std::string text, int x, int y);
};
