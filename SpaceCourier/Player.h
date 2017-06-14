#pragma once

#include "Vec3.h"
#include "Texture.h"
#include "Model.h"
#include "Object.h"

class Player : 
    public Object
{
public:
    Player();
    Player(vec3 position, vec3 direction, float speed);
    ~Player();

    virtual void update() override;
    virtual void render() override;

    void moveForward();
    void moveStop();
    void moveLeft();
    void moveLeftStop();
    void moveRight();
    void moveRightStop();
    void moveUp();
    void moveUpStop();
    void moveDown();
    void moveDownStop();
    void moveCamera(int mouseX, int mouseY);

private:
    Model* model;
    Texture* texture;

    vec3 direction;
    vec3 camera;

    float speed;
    float velocityX;
    float velocityZ;
    float velocityRX;
    float velocityRY;

    float maxAngleX;
    float maxAngleZ;

    bool isMovingForward;
    bool isMovingLeft;
    bool isMovingRight;
    bool isMovingUp;
    bool isMovingDown;

    int mouseX;
    int mouseY;
};
