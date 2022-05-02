//
// Created by Mark Ilovar on 01/05/2022.
//

#include "Animal.h"

void Animal::init() {
    SDL_Surface *tmp = SDL_LoadBMP("../assets/Idle.bmp");
    tex = SDL_CreateTextureFromSurface(Menu::renderer,tmp);
    SDL_FreeSurface(tmp);

    srcRect.w=srcRect.h=48;
    destRect.w=destRect.h = srcRect.w *2;

    position.x=rand()%1900;
    position.y = rand()%900;
}

void Animal::update() {
    srcRect.x=srcRect.w * static_cast<int>((SDL_GetTicks()/speed)%nFrames);

    destRect.x =position.x - Game::camera.x;
    destRect.y=position.y - Game::camera.y;
}

void Animal::draw() {
    SDL_RenderCopy(Menu::renderer, tex,  &srcRect, &destRect);
}

