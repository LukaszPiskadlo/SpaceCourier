#include <GL/freeglut.h>

#include "Game.h"

const int Game::updateTime = 17;
const char* Game::gameName = "Space Courier";
bool Game::keystate[255];

Game::Game()
    : windowWidth(854), windowHeight(480), windowPosX(100), windowPosY(100)
{
}

Game::~Game()
{
}

void Game::init(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitWindowPosition(windowPosX, windowPosY);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow(gameName);

    glutDisplayFunc(onRender);
    glutReshapeFunc(onReshape);
    glutKeyboardFunc(onKeyPress);
    glutKeyboardUpFunc(onKeyUp);
    glutPassiveMotionFunc(onMouseMove);
    glutMotionFunc(onMouseMove);
    glutTimerFunc(updateTime, onTimer, 0);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_NORMALIZE);

    glEnable(GL_LIGHTING);

    // disable global light
    float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

    // todo initialize game scene and camera

    glutMainLoop();
}

void Game::onRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // todo render here

    glutSwapBuffers();
    glFlush();
    glutPostRedisplay();
}

void Game::onReshape(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(50.0f, (float)width / height, 0.01f, 100.0f);
}

void Game::onKeyPress(unsigned char key, int x, int y)
{
    if (!keystate[key]) {
        keystate[key] = true;
        onKeyDown(key, x, y);
    }
}

void Game::onKeyDown(unsigned char key, int x, int y)
{
    if (key == ESC) {
        glutLeaveMainLoop();
    }
}

void Game::onKeyUp(unsigned char key, int x, int y)
{
    keystate[key] = false;
}

void Game::onMouseMove(int x, int y)
{
    // todo mosue movement
}

void Game::onTimer(int id)
{
    glutTimerFunc(updateTime, onTimer, id);

    // todo game scene update
}
