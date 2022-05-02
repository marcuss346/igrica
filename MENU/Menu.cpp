//
// Created by Mark Ilovar on 01/05/2022.
//

#include "Menu.h"
#include "../GAME/Game.h"
#include <fstream>
const int fps=60;
const int frameDelay=1000/fps;
Uint32 frameStart;
int frameTime;

SDL_Renderer *Menu::renderer;
SDL_Event Menu::event;

Game *game=NULL;

Menu::Menu(const char *title, int x, int y, int width, int height, bool fullscreen){
    std::cout<<"VNESI SVOJE IME: ";
    fgets(ime,50,stdin);
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL FAILED TO INITIALISE" << SDL_GetError() << std::endl;
        isRunning = false;
        return;
    }
    int flags = 0;
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;
    std::cout << "SDL successfully initialised!" << std::endl;
    window = SDL_CreateWindow(title, x, y, width, height, flags);
    if (window) {
        std::cout << "window created" << std::endl;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer)
        std::cout << "renderer created" << std::endl;
    isRunning = true;
}

void Menu::init(){
    SDL_Surface* assetBg = SDL_LoadBMP("../assets/background.bmp");
    background = SDL_CreateTextureFromSurface(Menu::renderer, assetBg);

    SDL_Surface* assetSelector = SDL_LoadBMP("../assets/selector.bmp");
    selector = SDL_CreateTextureFromSurface(Menu::renderer, assetSelector);
    active=true;
}

void Menu::update() {
    SDL_GetMouseState(&Mx,&My);
    selectorRect.x=Mx;
    selectorRect.y=My;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        else if(SDL_HasIntersection(&start, &selectorRect)){
            if(event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT){
                selection=0;
                select();
            }
        }
        else if(SDL_HasIntersection(&load, &selectorRect)){
            if(event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT){
                selection=1;
                select();
            }
        }
        else if(SDL_HasIntersection(&quit, &selectorRect))
            if(event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT){
                isRunning=false;
            }

    }
    //SDL_RenderClear(Menu::renderer);
    draw();
}

void Menu::draw() {
    SDL_RenderClear(Menu::renderer);

    SDL_RenderCopy(
            Menu::renderer,
            background,
            NULL,
            &render
    );


    SDL_RenderPresent(Menu::renderer);
}

void Menu::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    std::cout << "game cleaned" << std::endl;
}

void Menu::select() {
    switch (selection) {
        case 0:
            active=false;
            game = new Game();
            game->init_newGame(ime);
            while(game->isRunning) {
                game->handleEvents();
                game->update();
                game->render();

                frameTime = SDL_GetTicks() - frameStart;

                if (frameDelay > frameTime) {
                    SDL_Delay(frameDelay - frameTime);
                }
            }
            break;
        case 1:
            active=false;
            game = new Game();
            game->init_load();
            while(game->isRunning) {
                game->handleEvents();
                game->update();
                game->render();

                frameTime = SDL_GetTicks() - frameStart;

                if (frameDelay > frameTime) {
                    SDL_Delay(frameDelay - frameTime);
                }
            }
            break;
        case 2:
            active=false;
            game = new Game();
            game->init_replay();
            while(game->isRunning) {
                game->handleEvents();
                std::ifstream data("../assets/files/replay.txt");
                if(data.is_open()) {
                    int x,y;
                    while(data>>x>>y){
                    game->replayUpdate(x,y);
                    game->render();
                    }
                  game->isRunning=false;
                }
                data.close();
                frameTime = SDL_GetTicks() - frameStart;

                if (frameDelay > frameTime) {
                    SDL_Delay(frameDelay - frameTime);
                }
            }
            break;
    }
}

