//
// Created by Mark Ilovar on 01/05/2022.
//

#pragma once
#include "SDL.h"
#include "../VECTOR2D/Vector2D.h"
#include <cstring>

class Player{
    SDL_Texture *staying;
    SDL_Texture *walking;
    bool isWalking;

    int speed=100;
    int FramesWalking;
    int framesStanding;
    SDL_RendererFlip flip;

    float speedWalk=10;
    Vector2D velocity;

    const int fps=200;
    const int frameDelay=1000/fps;
    Uint32 frameStart = SDL_GetTicks();
    int frameTime;



public:
    int points=0;
    char ime[50];
    int lives= 5;
    Vector2D position;
    SDL_Rect srcRect, destRect;
    void init(char tmz[]);
    void update();
    void draw();
    void handleInput();
    void addPoints(int);
    void removeLife();
    void randLocation();
    int returnPoints();
    void izpis();
};
