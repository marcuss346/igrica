//
// Created by Mark Ilovar on 01/05/2022.
//

#pragma once
#include "SDL.h"
#include "iostream"
#include "../VECTOR2D/Vector2D.h"

class GameObject{
    SDL_Texture *texture;

    Vector2D position;

public:
    SDL_Rect destRect, srcRect;
    bool exsists;

    void init(const char *path,int w, int h);
    void update();
    void draw();
    void destroy();

};
