//
// Created by Mark Ilovar on 01/05/2022.
//

#include "GameObject.h"
#include "../MENU/Menu.h"
#include "../GAME/Game.h"

void GameObject::init(const char *path, int w, int h) {
    SDL_Surface *tmp=SDL_LoadBMP(path);
    texture = SDL_CreateTextureFromSurface(Menu::renderer,tmp);
    SDL_FreeSurface(tmp);

    position.x=position.y= 100;
    destRect.w=w;
    destRect.h=h;

    srcRect.w = 335;
    srcRect.h=310;
    srcRect.x=0;
    srcRect.y=0;
}

void GameObject::update() {
    destRect.x = position.x - Game::camera.x;
    destRect.y = position.y - Game::camera.y;
}

void GameObject::draw() {
    SDL_RenderCopy(Menu::renderer,texture,&srcRect,&destRect);
}
