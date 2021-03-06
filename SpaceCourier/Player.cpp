#include <GL\freeglut.h>

#include "Player.h"
#include "Settings.h"

Player::Player()
    : Player(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f), DEFAULT_SPEED)
{
}

Player::Player(vec3 position, vec3 direction, float speed)
{
    this->position = position;
    this->rotation = vec3(0.0f, 0.0f, 0.0f);
    this->direction = direction;
    this->speed = speed;

    camera = CAMERA_OFFSET;
    velocityX = 0.0f;
    velocityZ = 0.0f;
    velocityRX = 0.0f;
    velocityRY = 0.0f;

    maxAngleX = 30.0f;
    maxAngleZ = 20.0f;

    isMovingForward = false;
    isMovingLeft = false;
    isMovingRight = false;
    isMovingUp = false;
    isMovingDown = false;

    mouseX = 0;
    mouseY = 0;

    xMin = 0;
    xMax = 0;
    yMin = 0;
    yMax = 0;

    isDead = false;

    model = new Model("Resources\\space_frigate_6.obj");
    texture = new Texture("Resources\\space_frigate_6_color.png", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

    vec3 boxPosition1(position.x, position.y, position.z - 5.0f);
    collisionBoxes.push_back(new CollisionBox(boxPosition1, vec3(2.5f, 2.5f, 3.5f)));
    vec3 boxPosition2(position.x, position.y, position.z + 5.0f);
    collisionBoxes.push_back(new CollisionBox(boxPosition2, vec3(8.0f, 2.0f, 2.0f)));

    glEnable(GL_LIGHT1);
}

Player::~Player()
{
    delete texture;
    delete model;

    glDisable(GL_LIGHT1);
}

void Player::update()
{
    if (isDead)
    {
        return;
    }

    float t = acos(direction.y);
    float g = atan2(direction.z, direction.x);
    t += velocityRY * 0.06f / speed;
    g += velocityRX * 0.12f / speed;
    direction.x = sin(t) * cos(g);
    direction.y = cos(t);
    //direction.z = sin(t) * sin(g);

    float angleX = -maxAngleX / speed;
    float angleZ = maxAngleZ / speed;
    angleX *= velocityRX;
    angleZ *= velocityRY;

    float twoAxis = 1.0f;
    if ((angleX > 0.01f || angleX < -0.01f) && angleZ > 1.0f)
    {
        twoAxis *= -1.0f;
    }
    rotation = vec3(angleX * twoAxis, 0.0f, angleZ);
    vec3 per(-direction.z, direction.y, direction.x);

    vec3 nextPosition = position;
    nextPosition.x += direction.x * velocityX * 0.1f;
    nextPosition.y += direction.y * velocityX * 0.1f;
    nextPosition.z += direction.z * velocityX * 0.1f;

    nextPosition.x += per.x * velocityZ * 0.1f;
    nextPosition.y += per.y * velocityX * 0.1f;
    nextPosition.z += per.z * velocityZ * 0.1f;

    position = nextPosition;

    if (!isMovingForward)
    {
        velocityX /= 1.2f;
    }
    if (!isMovingLeft && !isMovingRight)
    {
        velocityRX /= 1.2f;
    }
    if (!isMovingUp && !isMovingDown)
    {
        velocityRY /= 1.2f;
    }

    direction.x /= 1.2f;
    direction.y /= 1.2f;

    vec3 boxPosition1(position.x, position.y, position.z - 5.0f);
    collisionBoxes[0]->setPosition(boxPosition1);
    vec3 boxPosition2(position.x, position.y, position.z + 5.0f);
    collisionBoxes[1]->setPosition(boxPosition2);
}

void Player::render()
{
    gluLookAt(
        // eye
        position.x + camera.x,
        position.y + camera.y,
        position.z + camera.z,
        // center
        position.x,
        position.y,
        position.z,
        // normal
        0.0f,
        1.0f,
        0.0f
    );

    if (isDead)
    {
        return;
    }

    float lightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float lightSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float lightPosition[] = { position.x, position.y - 1.5f, position.z - 9.0f, 1.0f };
    float lightDirection[] = { direction.x, direction.y, direction.z };
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDirection);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0f);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.05f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.04f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.03f);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 5.0f);

    glPushMatrix();

    float materialAmbDif[] = { 1.0f, 1.0f, 1.0f };
    float materialSpecular[] = { 0.0f, 0.0f, 0.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialAmbDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

    glTranslatef(position.x, position.y, position.z);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
    glScalef(0.5f, 0.5f, 0.5f);

    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texture->getId());
    glCallList(model->getId());

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    // (debug) show collision points
    //glPushMatrix();

    //vec3 cs = collisionBoxes[0]->getHalfSize();
    //vec3 cpos = collisionBoxes[0]->getPosition();
    //glPointSize(10.0f);

    ////glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    //glBegin(GL_POINTS);
    //glVertex3f(cpos.x + cs.x, cpos.y + cs.y, cpos.z + cs.z);
    //glVertex3f(cpos.x - cs.x, cpos.y + cs.y, cpos.z + cs.z);
    //glVertex3f(cpos.x - cs.x, cpos.y - cs.y, cpos.z + cs.z);
    //glVertex3f(cpos.x + cs.x, cpos.y - cs.y, cpos.z + cs.z);
    //glVertex3f(cpos.x + cs.x, cpos.y + cs.y, cpos.z - cs.z);
    //glVertex3f(cpos.x - cs.x, cpos.y + cs.y, cpos.z - cs.z);
    //glVertex3f(cpos.x - cs.x, cpos.y - cs.y, cpos.z - cs.z);
    //glVertex3f(cpos.x + cs.x, cpos.y - cs.y, cpos.z - cs.z);
    //glEnd();

    //glPopMatrix();

    //glPushMatrix();

    //cs = collisionBoxes[1]->getHalfSize();
    //cpos = collisionBoxes[1]->getPosition();
    //glPointSize(10.0f);

    ////glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    //glBegin(GL_POINTS);
    //glVertex3f(cpos.x + cs.x, cpos.y + cs.y, cpos.z + cs.z);
    //glVertex3f(cpos.x - cs.x, cpos.y + cs.y, cpos.z + cs.z);
    //glVertex3f(cpos.x - cs.x, cpos.y - cs.y, cpos.z + cs.z);
    //glVertex3f(cpos.x + cs.x, cpos.y - cs.y, cpos.z + cs.z);
    //glVertex3f(cpos.x + cs.x, cpos.y + cs.y, cpos.z - cs.z);
    //glVertex3f(cpos.x - cs.x, cpos.y + cs.y, cpos.z - cs.z);
    //glVertex3f(cpos.x - cs.x, cpos.y - cs.y, cpos.z - cs.z);
    //glVertex3f(cpos.x + cs.x, cpos.y - cs.y, cpos.z - cs.z);
    //glEnd();

    //glPopMatrix();
}

void Player::moveForward()
{
    velocityX = speed;
    isMovingForward = true;
}

void Player::moveStop()
{
    isMovingForward = false;
}

void Player::moveLeft()
{
    if (xMin != 0 && position.x < xMin)
    {
        isMovingLeft = false;
        return;
    }

    if (velocityRX == 0.0f)
    {
        velocityRX = -speed / 10.0f;
    }
    else if (velocityRX > -speed)
    {
        velocityRX--;
    }

    isMovingLeft = true;
}

void Player::moveLeftStop()
{
    isMovingLeft = false;
}

void Player::moveRight()
{
    if (xMax != 0 && position.x > xMax)
    {
        isMovingRight = false;
        return;
    }

    if (velocityRX == 0.0f)
    {
        velocityRX = speed / 10.0f;
    }
    else if (velocityRX < speed)
    {
        velocityRX++;
    }

    isMovingRight = true;
}

void Player::moveRightStop()
{
    isMovingRight = false;
}

void Player::moveUp()
{
    if (yMax != 0 && position.y > yMax)
    {
        isMovingUp = false;
        return;
    }

    if (velocityRY == 0.0f)
    {
        velocityRY = -speed / 10.0f;
    }
    else if (velocityRY > -speed)
    {
        velocityRY--;
    }

    isMovingUp = true;
}

void Player::moveUpStop()
{
    isMovingUp = false;
}

void Player::moveDown()
{
    if (yMin != 0 && position.y < yMin)
    {
        isMovingDown = false;
        return;
    }

    if (velocityRY == 0.0f)
    {
        velocityRY = speed / 10.0f;
    }
    else if (velocityRY < speed)
    {
        velocityRY++;
    }

    isMovingDown = true;
}

void Player::moveDownStop()
{
    isMovingDown = false;
}

void Player::moveCamera(int mouseX, int mouseY)
{
    this->mouseX = mouseX;
    this->mouseY = mouseY;
}

void Player::setSpeed(float speed)
{
    this->speed = speed;
}

void Player::setDead(bool isDead)
{
    this->isDead = isDead;

    if (isDead)
    {
        glDisable(GL_LIGHT1);
    }
}

void Player::setLimits(float xMin, float xMax, float yMin, float yMax)
{
    this->xMin = xMin;
    this->xMax = xMax;
    this->yMin = yMin;
    this->yMax = yMax;
}

bool Player::isAlive()
{
    return !isDead;
}

std::vector<CollisionBox*> Player::getCollisionBoxes()
{
    return collisionBoxes;
}
