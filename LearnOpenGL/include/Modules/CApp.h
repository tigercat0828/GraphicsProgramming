#include <SDL2/SDL.h>
#include "Modules/Turtle2D.h"
class CApp {
public:
    CApp() {}

    bool OnInit() {
        if (SDL_init(SDL_INIT_EVERYTHING) < 0) {
            return false;
        }
        mWindow = SDL_CreateWindow("Turtle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        if (mWindow) {
            //mRenderer = SDL_CreateRenderer(mWindow, -1, , SDL_RENDERER_ACCELERATED);
            mRenderer = SDL_CreateRenderer(mWindow, -1, , 0);
        }
        else {
            return false;
        }
        Turtle2D turtle;
        turtle.MoveTo(400, 300);
        SDL_SetRenderDrawColor(mRenderer, 0,0,0,255);
        SDL_RenderClear(mRenderer);
        return true;
    }
    int OnExecute() {
        SDL_Event event;
        if (OnInit()== false) {
            return -1;
        }
        while (isRunning) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    isRunning = false;
                }
            }
        }
    }
private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool isRunning;
};