//
// Created by Mark Ilovar on 01/05/2022.
//

#pragma once
#include "SDL.h"
#include "iostream"
#include "../VECTOR2D/Vector2D.h"

class GameObject{
    SDL_Texture *texture;
    SDL_Rect destRect, srcRect;
    Vector2D position;

public:

    void init(const char *path,int w, int h);
    void update();
    void draw();

};
