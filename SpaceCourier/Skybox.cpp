#include "Skybox.h"

const int Skybox::listCount = 6;
const float Skybox::scale = 50.0f;

Skybox::Skybox()
{
    spaceBoxUp = new Texture("Resources\\spaceboxUP.png", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
    spaceBoxBack = new Texture("Resources\\spaceboxBK.png", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
    spaceBoxDown = new Texture("Resources\\spaceboxDN.png", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
    spaceBoxFront = new Texture("Resources\\spaceboxFT.png", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
    spaceBoxLeft = new Texture("Resources\\spaceboxLF.png", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
    spaceboxRight = new Texture("Resources\\spaceboxRT.png", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

    listId[UP] = glGenLists(listCount);

    glNewList(listId[UP], GL_COMPILE);
    glBegin(GL_QUADS);

    // top
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    glEnd();
    glEndList();

    listId[FRONT] = glGenLists(listCount);

    glNewList(listId[FRONT], GL_COMPILE);
    glBegin(GL_QUADS);

    // front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    glEnd();
    glEndList();

    listId[DOWN] = glGenLists(listCount);

    glNewList(listId[DOWN], GL_COMPILE);
    glBegin(GL_QUADS);

    // bottom
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    glEnd();
    glEndList();

    listId[BACK] = glGenLists(listCount);

    glNewList(listId[BACK], GL_COMPILE);
    glBegin(GL_QUADS);

    // back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();
    glEndList();

    listId[LEFT] = glGenLists(listCount);

    glNewList(listId[LEFT], GL_COMPILE);
    glBegin(GL_QUADS);

    // left
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    glEnd();
    glEndList();

    listId[RIGHT] = glGenLists(listCount);

    glNewList(listId[RIGHT], GL_COMPILE);
    glBegin(GL_QUADS);

    // right
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    
    glEnd();
    glEndList();
}

Skybox::~Skybox()
{
    delete spaceBoxBack;
    delete spaceBoxDown;
    delete spaceBoxFront;
    delete spaceBoxLeft;
    delete spaceboxRight;
    delete spaceBoxUp;
}

void Skybox::update()
{
}

void Skybox::render()
{
    glPushMatrix();

    glTranslatef(position.x, position.y, position.z);
    glScalef(scale, scale, scale);

    glEnable(GL_TEXTURE_2D);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, spaceBoxUp->getId());
    glCallList(listId[UP]);

    glBindTexture(GL_TEXTURE_2D, spaceBoxFront->getId());
    glCallList(listId[FRONT]);

    glBindTexture(GL_TEXTURE_2D, spaceBoxDown->getId());
    glCallList(listId[DOWN]);

    glBindTexture(GL_TEXTURE_2D, spaceBoxBack->getId());
    glCallList(listId[BACK]);
    
    glBindTexture(GL_TEXTURE_2D, spaceBoxLeft->getId());
    glCallList(listId[LEFT]);

    glBindTexture(GL_TEXTURE_2D, spaceboxRight->getId());
    glCallList(listId[RIGHT]);

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
