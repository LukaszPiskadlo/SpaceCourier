#include "Game.h"

int main(int argc, char* argv[])
{
    Game* game = new Game();
    game->init(&argc, argv);

    delete game;

    return 0;
}
