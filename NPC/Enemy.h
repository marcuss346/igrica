//
// Created by Mark Ilovar on 02/05/2022.
//

#pragma once
#include "SDL.h"
#include "../VECTOR2D/Vector2D.h"

class Enemy{
private:
    SDL_Texture *textrue;


    int speed=100;
    int nFrames = 6;
    int speeds = 2;

    const int fps=200;
    const int frameDelay=1000/fps;
    Uint32 frameStart = SDL_GetTicks();
    int frameTime;

public:
    Vector2D position;
    Vector2D velocity;
    SDL_Rect srcRect, destRect;

    void init();
    void update();
    void draw();
};