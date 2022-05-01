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

class Map;
class Animal;

class Game{


    bool replayB;
    SDL_Window *window;
    std::vector<Animal> animals;


public:
    bool isRunning;
    static SDL_Event event;
    static SDL_Rect camera;

    Game();
    void init_newGame();
    void init_load();
    void init_replay();
    void handleEvents();
    void update();
    void render();
    void clean();

    void saveState();
    void replayUpdate(int x ,int y);

    void addAnimal();


};

