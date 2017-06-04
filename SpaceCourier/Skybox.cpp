#include "Skybox.h"

const int Skybox::listCount = 1;

Skybox::Skybox()
{
    listId = glGenLists(listCount);

    glNewList(listId, GL_COMPILE);
    glBegin(GL_QUADS);

    // front
    glNormal3f(0.0f, 0.0f, 1.0f);

    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // back
    glNormal3f(0.0f, 0.0f, -1.0f);

    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // left
    glNormal3f(-1.0f, 0.0f, 0.0f);

    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // right
    glNormal3f(1.0f, 0.0f, 0.0f);

    glVertex3f(1.0f, 0.0f, -1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // bottom
    glNormal3f(0.0f, -1.0f, 0.0f);

    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    glEnd();
    glEndList();
}

Skybox::~Skybox()
{
}

void Skybox::update()
{
}

void Skybox::render()
{
    glPushMatrix();

    glTranslatef(1.0f, 0.0f, 0.0f);
    glCallList(listId);

    glPopMatrix();
}
