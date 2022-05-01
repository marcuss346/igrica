//
// Created by Mark Ilovar on 01/05/2022.
//

#pragma once
#include "SDL.h"
#include "../VECTOR2D/Vector2D.h"

class Player{
    SDL_Texture *staying;
    SDL_Texture *walking;
    bool isWalking;

    int speed=100;
    int FramesWalking;
    int framesStanding;
    SDL_RendererFlip flip;

    float speedWalk=20;
    Vector2D velocity;

    int points=0;



public:
    Vector2D position;
    SDL_Rect srcRect, destRect;
    void init();
    void update();
    void draw();
    void handleInput();
    void addPoints(int);
};
