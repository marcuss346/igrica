#define SDL_MAIN_HANDLED
#include <iostream>
#include "SDL.h"
#include "GAME/Game.h"
#include "MENU/Menu.h"
#include "ctime"


int main(int argc, const char *argv[]) {
    srand(time(NULL));
    Menu *game=new Menu("new game",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, 0);
   game->init();
    while(game->isRunning){
       game->update();
    }
    game->clean();
    return 0;
}
