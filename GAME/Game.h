//
// Created by Mark Ilovar on 01/05/2022.
//

#pragma once
#include "SDL.h"
#include <iostream>
#include "../MAP/Map.h"
#include "../PLAYER/Player.h"
#include "../NPC/Animal.h"
#include "vector"
#include "../GAMEOBJECT/GameObject.h"
#include "../NPC/Enemy.h"

class Map;
class Animal;

class Game{


    bool replayB;
    SDL_Window *window;
    std::vector<Animal> animals;
    std::vector<Enemy> enemies;

    std::ifstream berem;

public:
    bool isRunning;
    static SDL_Event event;
    static SDL_Rect camera;

    Game();
    void init_newGame(char tmp[]);
    void init_load();
    void init_replay();
    void handleEvents();
    void update();
    void render();
    void clean();

    void saveState();

    void addAnimal();
    void addEnemy();


    void replayUpdate();

    void renderReplay();
};

