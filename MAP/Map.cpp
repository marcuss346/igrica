//
// Created by Mark Ilovar on 01/05/2022.
//

#include "Map.h"


void Map::init(int level, SDL_Renderer *ren) {
    switch(level){
        case 1:
            SDL_Surface *tmp=SDL_LoadBMP("../assets/tiles.bmp");
            map= SDL_CreateTextureFromSurface(Menu::renderer, tmp);
            break;
    }
}

void Map::update() {
    destRect.x =-Game::camera.x;
    destRect.y =-Game::camera.y;
    destRect.w = 3000;
    destRect.h = 2000;
}

void Map::draw() {
    SDL_RenderCopy(Menu::renderer, map, NULL,&destRect);
}