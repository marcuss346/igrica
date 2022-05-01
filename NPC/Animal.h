//
// Created by Mark Ilovar on 01/05/2022.
//

#pragma once
#include "SDL.h"
#include "../VECTOR2D/Vector2D.h"
#include "../MENU/Menu.h"
#include "../GAME/Game.h"

class Animal{
    SDL_Texture *tex;
    SDL_Rect srcRect;


    int speed=100;
    int nFrames=4;

public:
    Vector2D position;
    SDL_Rect destRect;

    void init();
    void update();
    void draw();
    void saveState();

};
