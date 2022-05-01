//
// Created by Mark Ilovar on 01/05/2022.
//

#pragma once
#include "SDL.h"
#include "../GAME/Game.h"
#include "../MENU/Menu.h"

class Map{
    SDL_Texture *map;
    SDL_Rect destRect;
    SDL_Renderer *ren;

public:
    Map(){}
    void init(int level,SDL_Renderer *ren);
    void update();
    void draw();
};
