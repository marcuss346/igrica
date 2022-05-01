//
// Created by Mark Ilovar on 01/05/2022.
//

#pragma once
#include "SDL.h"
#include "iostream"

class Menu{
    SDL_Window *window;

    SDL_Texture *selector;
    SDL_Texture *background;
    bool active;
    int selection;

    int Mx, My;

    SDL_Rect start = {
            0,
            0,
            800,
            213
    };

    SDL_Rect load = {
            0,
            213,
            800,
            213,
    };

    SDL_Rect quit = {
            0,
            416,
            800,
            213
    };

    SDL_Rect render = {
            0,
            0,
            800,
            640
    };

    SDL_Rect selectorRect = {
            0,
            0,
            50,
            50
    };

public:
    bool isRunning;
    static SDL_Renderer *renderer;
    static SDL_Event event;
    Menu(const char *title, int x, int y, int width, int height, bool fullscreen);
    void init();
    void clean();
    void handleEvents();
    void draw();
    void renders();



    void setSelection();
    int getSelection();

    void moveDown();
    void moveUp();
    void select();
    void update();
    void setScreen(int);

};
