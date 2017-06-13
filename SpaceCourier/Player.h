#pragma once

#include "Vec3.h"
#include "Texture.h"
#include "Model.h"

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
    void moveStop();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void moveCamera(int mouseX, int mouseY);

private:
    static const float mouseSensitivity;

    Model* model;
    Texture* texture;

    vec3 position;
    vec3 rotation;
    vec3 direction;
    vec3 camera;

    float speed;
    float velocityX;
    float velocityZ;
    float velocityRX;
    float velocityRY;

    bool isMoving;

    int mouseX;
    int mouseY;
};
