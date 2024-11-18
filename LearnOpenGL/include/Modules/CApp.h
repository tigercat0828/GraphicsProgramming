#include <SDL2/SDL.h>
#include "Modules/Turtle2D.h"
#include <vector>
using namespace std;
class CApp {
public:
    CApp() {
        mIsRunning = true;
        mWindow = nullptr;
        mRenderer = nullptr;
        reds.push_back(51); greens.push_back(128); blues.push_back(204);
        reds.push_back(255); greens.push_back(128); blues.push_back(0);
        reds.push_back(255); greens.push_back(191); blues.push_back(0);
    }

    bool OnInit() {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            return false;
        }
        mWindow = SDL_CreateWindow("Turtle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        if (mWindow) {
            //mRenderer = SDL_CreateRenderer(mWindow, -1,  SDL_RENDERER_ACCELERATED);
            mRenderer = SDL_CreateRenderer(mWindow, -1,  0);
        }
        else {
            return false;
        }
        mTurtle.MoveTo(400, 300);
        SDL_SetRenderDrawColor(mRenderer, 0,0,0,255);
        SDL_RenderClear(mRenderer);
        mTurtle.SetRenderer(mRenderer);
        mTurtle.PenDown();
        mTurtle.SetLength(75);
        mTurtle.Step();
        for (int i = 0; i < 18; i++) {
            mTurtle.SetPenColor(reds[i%3], greens[i%3], blues[i%3],255);
            for (int j = 0; j < 8; j++) {
                mTurtle.RotateRight(45);
                mTurtle.Step();
            }
            mTurtle.RotateLeft(20);
        }
        SDL_RenderPresent(mRenderer);
        return true;
    }
    int OnExecute() {
        SDL_Event event;
        if (OnInit()== false) {
            return -1;
        }
        while (mIsRunning) {
            while (SDL_PollEvent(&event)!= 0) {
               OnEvent(&event);
            }
            OnLoop();
            OnRender();
        }
        OnExit();
        return 0;
    }
    void OnEvent(SDL_Event* event) {
        if (event->type == SDL_QUIT) {
            mIsRunning = false;
        }
    }
    void OnLoop() {
    }
    void OnRender() {
        SDL_SetRenderDrawColor(mRenderer, 0,0,0,255);
        SDL_RenderClear(mRenderer);
        //SDL_Rect rect = { 150,120,300,200 };
        //SDL_SetRenderDrawColor(mRenderer, 0,0,255,255);
        //SDL_RenderFillRect(mRenderer, &rect);
        //
        //// show the result
        //SDL_RenderPresent(mRenderer);
    }
    void OnExit() {
        SDL_DestroyRenderer(mRenderer);
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
        SDL_Quit();
    }
private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool mIsRunning;
    Turtle2D mTurtle;

    vector<char> reds;
    vector<char> greens;
    vector<char> blues;
};