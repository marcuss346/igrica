//
// Created by Mark Ilovar on 02/05/2022.
//

#include "Enemy.h"
#include "../GAME/Game.h"
#include "../MENU/Menu.h"

void Enemy::init() {
    SDL_Surface *tmp = SDL_LoadBMP("../assets/Walk.bmp");
    textrue = SDL_CreateTextureFromSurface(Menu::renderer,tmp);
    SDL_FreeSurface(tmp);

    srcRect.w=srcRect.h=48;
    destRect.w=destRect.h = srcRect.w *2;

    position.x=rand()%1900;
    position.y = rand()%900;
}

void Enemy::update() {
    srcRect.x=srcRect.w * static_cast<int>((SDL_GetTicks()/speed)%nFrames);

    position.x += velocity.x *speeds;
    position.y += velocity.y *speeds;

    destRect.x =position.x - Game::camera.x;
    destRect.y=position.y - Game::camera.y;
}

void Enemy::draw() {
    SDL_RenderCopy(Menu::renderer, textrue,  &srcRect, &destRect);
}
