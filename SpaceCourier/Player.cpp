#include <GL\freeglut.h>

#include "Player.h"

const float Player::mouseSensitivity = 0.15f;

Player::Player()
    : Player(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f), 3.0f)
{
}

Player::Player(vec3 position, vec3 direction, float speed)
{
    this->position = position;
    this->direction = direction;
    this->speed = speed;

    camera.set(0.0f, 5.0f, 30.0f);
    velocityX = 0.0f;
    velocityZ = 0.0f;
    velocityRX = 0.0f;
    velocityRY = 0.0f;

    mouseX = 0;
    mouseY = 0;

    model = new Model("Resources\\space_frigate_6.obj");
    texture = new Texture("Resources\\space_frigate_6_color.png", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
}

Player::~Player()
{
    delete texture;
    delete model;
}

void Player::update()
{
    velocityRY = -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX);
    velocityRX = mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY);
    glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);

    float t = acos(direction.y);
    float g = atan2(direction.z, direction.x);
    t -= velocityRX * 0.03f;
    g += velocityRY * 0.03f;
    direction.x = sin(t) * cos(g);
    direction.y = cos(t);
    direction.z = sin(t) * sin(g);

    vec3 per(-direction.z, 0, direction.x);

    vec3 nextPosition = position;
    nextPosition.x += direction.x * velocityX * 0.1f;
    nextPosition.y += direction.y * velocityX * 0.1f;
    nextPosition.z += direction.z * velocityX * 0.1f;

    nextPosition.x += per.x * velocityZ * 0.1f;
    nextPosition.y += direction.y * velocityX * 0.1f;
    nextPosition.z += per.z * velocityZ * 0.1f;

    position = nextPosition;

    velocityX /= 1.2f;
    velocityZ /= 1.2f;
    velocityRX /= 1.2f;
    velocityRY /= 1.2f;
}

void Player::render()
{
    gluLookAt(
        position.x + camera.x, position.y + camera.y, position.z + camera.z,
        position.x + camera.x + direction.x, position.y + camera.y + direction.y, position.z + camera.z + direction.z,
        0.0f, 1.0f, 0.0f
    );

    glPushMatrix();

    float mA[] = { 1.0f, 1.0f, 1.0f };
    float mS[] = { 0.0f, 0.0f, 0.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mA);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mS);

    glTranslatef(position.x, position.y, position.z);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.5f, 0.5f, 0.5f);

    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, texture->getId());
    glCallList(model->getId());

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

vec3 Player::getPosition()
{
    return position;
}

void Player::moveForward()
{
    velocityX = speed;
}

void Player::moveBackward()
{
    velocityX = -speed;
}

void Player::moveLeft()
{
    velocityZ = -speed;
}

void Player::moveRight()
{
    velocityZ = speed;
}

void Player::moveCamera(int mouseX, int mouseY)
{
    this->mouseX = mouseX;
    this->mouseY = mouseY;
}
