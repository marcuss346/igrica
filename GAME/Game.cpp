//
// Created by Mark Ilovar on 01/05/2022.
//

#include "Game.h"
#include "fstream"
#include <vector>
Map *map;
Player *player;
GameObject *lab;

struct Ldrbrd{
    char ime[50];
    int points;
};



SDL_Event Game::event;
SDL_Rect Game::camera {
        0, 0 , 2000, 1000
};


Game::Game() {
    isRunning=true;
    map=new Map();
    player = new Player();
    lab=new GameObject;


}
    void Game::init_newGame(char tmp[]) {
        map->init(1,Menu::renderer);
        player->init(tmp);
        lab->init("../assets/lab.bmp",100,100);
        for(int i=0;i<3;i++){
            addEnemy();
        }

        std::ofstream data("../assets/files/replay.txt");
        data.close();

    }

    void Game::init_replay() {
        map->init(1,Menu::renderer);


}

    void Game::handleEvents() {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                isRunning=false;
                remove("../assets/files/save.bin");
                std::ofstream tmp("../assets/files/tmp.bin", std::ios::binary);
                std::ifstream ldb("../assets/files/leaderboard.bin", std::ios::binary);
                struct Ldrbrd nova;
                strcpy(nova.ime, player->ime);
                nova.points = player->points;
                bool vpisan = false;
                int vpisanih=0;
                if(ldb.is_open()){

                    for(int i=0;i<5;i++) {
                        struct Ldrbrd neki;
                         if(ldb.read((char *) &neki, sizeof(neki))) {
                            if (neki.points < nova.points && !vpisan) {
                                vpisan = true;
                                tmp.write((char *) &nova, sizeof(nova));
                                vpisanih++;
                            }
                            if(tmp.write((char *) &neki, sizeof(neki)))vpisanih++;
                        }
                    }
                    if(vpisanih<5 && !vpisan){
                        tmp.write((char *) &nova, sizeof(nova));
                    }
                } if(vpisanih < 5 && !vpisan){
                    tmp.write((char*)&nova, sizeof (nova));
                }

                tmp.close();
                ldb.close();

                remove("../assets/files/leaderboard.bin");
                rename("../assets/files/tmp.bin", "../assets/files/leaderboard.bin" );
                break;
        }

        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE){
            isRunning=false;
            saveState();
        }

        if(player->lives == 0){
            isRunning=false;
            remove("../assets/files/save.bin");
        }
}

    void Game::update() {
        player->update();
        for(int t=0;t<animals.size();t++){
            animals[t].update();
        }
        if(lab->exsists)
        lab->update();
        map->update();
        for(int t=0;t<enemies.size();t++){
            enemies[t].update();
        }
        std::ofstream data("../assets/files/replay.txt", std::ios::app);
        data<<player->position.x<<std::endl;
        data<<player->position.y<<std::endl;
        data.close();

        int i=0;
        for(int t=0;t<animals.size();t++) {
            if (SDL_HasIntersection(&animals[t].destRect, &player->destRect)
            && (event.type==SDL_KEYDOWN && event.key.keysym.sym == SDLK_c)){
                animals.erase(animals.begin() + i, animals.begin()+i+1);
                player->points += 50;
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

        if(animals.empty() && !lab->exsists){
            lab->init("../assets/lab.bmp",100,100);
        }



        camera.x = player->position.x - 800 / 2;
        camera.y = player->position.y - 640 / 2;

        for(int t=0;t<enemies.size();t++){
            if(player->position.x > enemies[t].position.x){
                enemies[t].velocity.x =1;
            }else if(player->position.x < enemies[t].position.x) {
                enemies[t].velocity.x = -1;
            }if(player->position.y > enemies[t].position.y){
                enemies[t].velocity.y =1;
            }else if(player->position.y < enemies[t].position.y) {
                enemies[t].velocity.y = -1;
            }
        }

        i=0;
        for(int t=0;t<enemies.size();t++) {
            if (SDL_HasIntersection(&enemies[t].destRect, &player->destRect)){
                player->removeLife();
                player->addPoints(-10);
                player->randLocation();
            }
            i++;
        }


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
            if(lab->exsists)
            lab->draw();

        for(int t=0;t<enemies.size();t++){
            enemies[t].draw();
        }
        if(!replayB)
            for(int t=0;t<animals.size();t++){
                animals[t].draw();
            }

        SDL_RenderPresent(Menu::renderer);
    }

    void Game::saveState() {
        std::ofstream data("../assets/files/save.bin", std::ios::binary);
        std::ofstream velikosti("../assets/files/velikosti.txt");

        data.write((char *)&map, sizeof (map));
        data.write((char *)&player, sizeof(player));
        data.write((char *)&lab,sizeof (lab));
        int velikostAni = animals.size();
        velikosti<<velikostAni<<std::endl;
        int velikostEne = enemies.size();
        velikosti<<velikostEne<<std::endl;
        velikosti.close();
        for(int t=0;t<velikostAni;t++) {
            data.write((char *)&animals[t], sizeof (animals[t]));
        }
        for(int t=0;t<velikostEne;t++) {
            data.write((char *)&enemies[t], sizeof (enemies[t]));
        }

        data.close();
    }

    void Game::init_load() {
        map->init(1,Menu::renderer);
        std::ifstream data("../assets/files/save.bin", std::ios::binary);
        if(data.is_open()){
            data.read((char *)&map, sizeof (map));
            data.read((char *)&player, sizeof(player));
            data.read((char *)&lab, sizeof (lab));
            std::ifstream velikosti("../assets/files/velikosti.txt");
            int sizeAnim; velikosti>>sizeAnim; int sizeEnem; velikosti>>sizeEnem; velikosti.close();
            for(int i=0;i<sizeAnim;i++){
                Animal tmp;
                data.read((char*)&tmp, sizeof(tmp));
                animals.push_back(tmp);
            }
            for(int i=0;i<sizeEnem;i++){
                Enemy tmp;
                data.read((char*)&tmp, sizeof(tmp));
                enemies.push_back(tmp);
            }
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

void Game::addEnemy(){
    Enemy *tmp=new Enemy();
    tmp->init();
    enemies.push_back(*tmp);
}


