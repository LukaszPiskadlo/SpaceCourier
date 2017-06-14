#include <GL/freeglut.h>

#include "Game.h"
#include "Settings.h"

const int Game::updateTime = GAME_UPDATE_TIME;
const char* Game::gameName = GAME_NAME;
bool Game::keystate[255];
Scene* Game::scene = nullptr;

Game::Game()
    : windowWidth(WINDOW_WIDTH), windowHeight(WINDOW_HEIGHT), windowPosX(WINDOW_POS_X), windowPosY(WINDOW_POS_Y)
{
}

Game::~Game()
{
}

void Game::init(int* argc, char** argv)
{
    glutInit(argc, argv);

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
    glShadeModel(GL_SMOOTH);

    // disable global light
    float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

    glutSetCursor(GLUT_CURSOR_NONE);

    glutFullScreen();

    if (scene == nullptr)
    {
        scene = new Scene();
    }

    scene->init();

    glutMainLoop();
}

void Game::onRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    scene->render();

    glutSwapBuffers();
    glFlush();
    glutPostRedisplay();
}

void Game::onReshape(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(50.0f, (float)width / height, 0.01f, MAX_VIEW_DISTANCE);
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
    if (key == FULLSCREEN)
    {
        glutFullScreenToggle();
    }
}

void Game::onKeyUp(unsigned char key, int x, int y)
{
    keystate[key] = false;
}

void Game::onMouseMove(int x, int y)
{
    scene->player->moveCamera(x, y);
}

void Game::onTimer(int id)
{
    glutTimerFunc(updateTime, onTimer, id);

    if (keystate[MOVE])
    {
        scene->player->moveForward();
    }
    if (keystate[LEFT])
    {
        scene->player->moveLeft();
    }
    else
    {
        scene->player->moveLeftStop();
    }
    if (keystate[RIGHT])
    {
        scene->player->moveRight();
    }
    else
    {
        scene->player->moveRightStop();
    }
    if (keystate[UP])
    {
        scene->player->moveUp();
    }
    else
    {
        scene->player->moveUpStop();
    }
    if (keystate[DOWN])
    {
        scene->player->moveDown();
    }
    else
    {
        scene->player->moveDownStop();
    }

    scene->update();
}

