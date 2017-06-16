#include "Menu.h"

#include <GL\freeglut.h>

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::startGame()
{
    int width = glutGet(GLUT_SCREEN_WIDTH);
    int height = glutGet(GLUT_SCREEN_HEIGHT);

    std::string text = "Press Space";

    displayText(text, 20, 20);
}

void Menu::gameOver()
{
}

MissionDifficulty Menu::nextMission()
{
    return MissionDifficulty();
}

void Menu::render()
{
}

void Menu::displayText(std::string text, int x, int y)
{
    glPushMatrix();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    gluOrtho2D(0, width, 0, height);

    glTranslatef(CAMERA_OFFSET.x, CAMERA_OFFSET.y, CAMERA_OFFSET.z);

    glPushMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(x, y);

    for each (char letter in text)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
    }

    glPopMatrix();

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
}
