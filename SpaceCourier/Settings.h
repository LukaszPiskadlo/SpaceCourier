#pragma once

#include "Vec3.h"

enum Keys
{
    ESC = 27,
    MOVE = ' ',
    STOP = 'b',
    LEFT = 'a',
    RIGHT = 'd',
    UP = 'w',
    DOWN = 's',
    FULLSCREEN = 'h'
};

enum GameWindow
{
    WINDOW_WIDTH = 1280,
    WINDOW_HEIGHT = 720,
    WINDOW_POS_X = 100,
    WINDOW_POS_Y = 50
};

extern const char* GAME_NAME;
extern const int GAME_UPDATE_TIME;
extern const double MAX_VIEW_DISTANCE;

// skybox
extern const float SKYBOX_SCALE;

// player
extern const float DEFAULT_SPEED;
extern const vec3 CAMERA_OFFSET;
