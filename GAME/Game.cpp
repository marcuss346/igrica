//
// Created by Mark Ilovar on 01/05/2022.
//

#include "Game.h"
#include "fstream"
#include <vector>
Map *map;
Player *player;
GameObject *lab;



SDL_Event Game::event;
SDL_Rect Game::camera {
        0, 0 , 1200, 800
};


Game::Game() {
    isRunning=true;
    map=new Map();
    player = new Player();
    lab=new GameObject;


}
    void Game::init_newGame() {
        map->init(1,Menu::renderer);
        player->init();
        lab->init("../assets/lab.bmp",100,100);

        std::ofstream data("../assets/files/replay.txt");
        data.close();

    }

    void Game::init_replay() {
        map->init(1,Menu::renderer);
        player->init();

}

    void Game::handleEvents() {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                isRunning=false;
                break;
        }

        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE){
            isRunning=false;
            saveState();
        }
}

    void Game::update() {
        player->update();
        for(int t=0;t<animals.size();t++){
            animals[t].update();
        }
        lab->update();
        map->update();
        std::ofstream data("../assets/files/replay.txt", std::ios::app);
        data<<player->position.x<<std::endl;
        data<<player->position.y<<std::endl;
        data.close();

        int i=0;
        for(int t=0;t<animals.size();t++) {
            if (SDL_HasIntersection(&animals[t].destRect, &player->destRect)
            && (event.type==SDL_KEYDOWN && event.key.keysym.sym == SDLK_c)){
                animals.erase(animals.begin() + i, animals.begin()+i+1);
            }
            i++;
        }

        if(SDL_HasIntersection(&lab->destRect, &player->destRect) &&
                event.type==SDL_KEYDOWN && event.key.keysym.sym == SDLK_k){
            lab->destroy();
            for(int i=0;i<3;i++){
                addAnimal();
            }
        }

        if(animals.empty()){
            lab->init("../assets/lab.bmp",100,100);
        }

        camera.x = player->position.x - 800 / 2;
        camera.y = player->position.y - 640 / 2;

        if( camera.x < 0 )
        {
            camera.x = 0;
        }
        if( camera.y < 0 )
        {
            camera.y = 0;
        }
        if( camera.x > camera.w )
        {
            camera.x = camera.w;
        }
        if( camera.y > camera.h)
        {
            camera.y = camera.h;
        }
}

    void Game::render() {
        SDL_RenderClear(Menu::renderer);


            map->draw();
            player->draw();
            lab->draw();


        if(!replayB)
            for(int t=0;t<animals.size();t++){
                animals[t].draw();
            }

        SDL_RenderPresent(Menu::renderer);
    }

    void Game::saveState() {
        std::ofstream data("../assets/files/save.bin", std::ios::binary);

        data.write((char *)&map, sizeof (map));
        data.write((char *)&player, sizeof(player));
        //data.write((char *)&animal, sizeof (animal));

        data.close();
    }

    void Game::init_load() {
        map->init(1,Menu::renderer);
        std::ifstream data("../assets/files/save.bin", std::ios::binary);
        if(data.is_open()){
            data.read((char *)&map, sizeof (map));
            data.read((char *)&player, sizeof(player));
           // data.read((char *)&animal, sizeof(animal));
            data.close();
        }else{
            std::cout<<"no file.. closing"<<std::endl;
            isRunning=false;
        }
}

void Game::replayUpdate(int x ,int y) {
    replayB=true;
    player->position.x=x;
    player->position.y=y;
}

void Game::addAnimal(){
    Animal *tmp=new Animal();
    tmp->init();
    animals.push_back(*tmp);
}


