#define SDL_MAIN_HANDLED
#include <iostream>
#include "SDL.h"
#include "GAME/Game.h"
#include "MENU/Menu.h"
#include "ctime"
#include "fstream"
#include "PLAYER/Player.h"
#include "string"

struct Ldrbrd{
    char ime[50];
    int points;
};

int main(int argc, const char *argv[]) {
    srand(time(NULL));

    std::string fsc;
    std::cout<<"VPISI ALI ZELIS FULLSCREEN: vpisi yes za da in no za ne: ";
    getline(std::cin,fsc);
    bool f;
    if(fsc=="YES" or fsc=="yes") f=true; else f=false;

    Menu *game=new Menu("new game",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, f);
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
        for(int i=0;i<5;i++){
        data.read((char*)&tmp, sizeof(tmp));
            std::cout<<"IME: "<<tmp.ime << "      "<<"TOCKE: "<<tmp.points<<std::endl;
            std::cout<<"---------------------------------------"<<std::endl;
        }
    }
    return 0;
}
