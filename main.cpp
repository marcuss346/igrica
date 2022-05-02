#define SDL_MAIN_HANDLED
#include <iostream>
#include "SDL.h"
#include "GAME/Game.h"
#include "MENU/Menu.h"
#include "ctime"
#include "fstream"
#include "PLAYER/Player.h"

struct Ldrbrd{
    char ime[50];
    int points;
};

int main(int argc, const char *argv[]) {
    srand(time(NULL));
    Menu *game=new Menu("new game",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, 0);
   game->init();
    while(game->isRunning){
       game->update();
    }
    game->clean();

    std::ifstream data("../assets/files/leaderboard.bin", std::ios::binary);
    if(data.is_open()){
        Ldrbrd tmp;
        std::cout<<"leaderboard"<<std::endl;
        std::cout<<"---------------------------------------"<<std::endl;
        while(data.read((char*)&tmp, sizeof(tmp))){
            std::cout<<"IME: "<<tmp.ime << "      "<<"TOCKE: "<<tmp.points<<std::endl;
            std::cout<<"---------------------------------------"<<std::endl;
        }
    }
    return 0;
}
