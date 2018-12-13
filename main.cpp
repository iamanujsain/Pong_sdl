#include <stdio.h>
#include <SDL2/SDL.h>
#include "Game.h"

int main(int argc, char** argv)
{
    Game game("Pong",
              400,
              600,
              false);
    game.run();
    return 0;
}
