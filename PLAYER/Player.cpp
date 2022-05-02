//
// Created by Mark Ilovar on 01/05/2022.
//

#include "Player.h"
#include "../GAME/Game.h"
#include <iomanip>

void Player::init(char tmz[]) {
    strcpy(ime,tmz);
    position.x=0;
    position.y=0;
    SDL_Surface *tmp = SDL_LoadBMP("../assets/Player_idle.bmp");
    staying = SDL_CreateTextureFromSurface(Menu::renderer,tmp);
    tmp=SDL_LoadBMP("../assets/Player_walk.bmp");
    walking= SDL_CreateTextureFromSurface(Menu::renderer, tmp);
    isWalking=false;

    srcRect.h=destRect.h=48;
    srcRect.w=destRect.w=48;
    framesStanding=4;
    FramesWalking=6;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void Player::update() {

    handleInput();
    position.x += velocity.x * speedWalk;
    position.y += velocity.y * speedWalk;

    if(isWalking)
        srcRect.x=srcRect.w * static_cast<int>((SDL_GetTicks()/speed)%FramesWalking);
    else
        srcRect.x=srcRect.w * static_cast<int>((SDL_GetTicks()/speed)%framesStanding);


    destRect.x =position.x - Game::camera.x;
    destRect.y=position.y - Game::camera.y;

}

void Player::draw() {
    if(isWalking){
        SDL_RenderCopyEx(Menu::renderer, walking,&srcRect,&destRect,0,NULL,flip);
    }else{
        SDL_RenderCopyEx(Menu::renderer, staying, &srcRect,&destRect,0,NULL,flip);
    }
}

void Player::handleInput() {
    if(Game::event.type==SDL_KEYDOWN){
        isWalking=true;
        switch (Game::event.key.keysym.sym) {
            case SDLK_w:
                velocity.y=-1;
                break;
            case SDLK_a:
                velocity.x=-1;
                flip=SDL_FLIP_HORIZONTAL;
                break;
            case SDLK_s:
                velocity.y=1;
                break;
            case SDLK_d:
                velocity.x=1;
                break;
            case SDLK_ESCAPE:
                Game::event.type=SDL_QUIT;
                break;
        }
    }
    if(Game::event.type==SDL_KEYUP){
        isWalking=false;
        switch (Game::event.key.keysym.sym) {
            case SDLK_w:
                velocity.y=0;
                break;
            case SDLK_a:
                velocity.x=0;
                flip=SDL_FLIP_NONE;
                break;
            case SDLK_s:
                velocity.y=0;
                break;
            case SDLK_d:
                velocity.x=0;
                break;
        }
    }
}

void Player::addPoints(int n) {
    points += n;
}

void Player::removeLife() {
    lives--;
}

void Player::randLocation(){
    position.x = rand()%1900;
    position.y = rand()%900;
}


