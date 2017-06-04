#pragma once

#include "Vec3.h"

class Player
{
public:
    Player();
    Player(vec3 position, vec3 direction, float speed);
    ~Player();

    void update();
    void render();

    vec3 getPosition();
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void moveCamera(float mouseX, float mouseY);

private:
    static const float mouseSensitivity;

    vec3 position;
    vec3 direction;
    vec3 camera;

    float speed;
    float velocityX;
    float velocityZ;
    float velocityRX;
    float velocityRY;

    float mouseX;
    float mouseY;
};
