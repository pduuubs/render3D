#include <SDL/SDL.h>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

#include "screen.h"

int w, h;

SDL_Surface* screen;

void initScreen(int width, int height, bool fullscreen, const std::string& title){
        int colorDepth = 32;
        w = width;
        h = height;

        if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
                SDL_Quit();
                std::exit(1);
        }

        std::atexit(SDL_Quit);

        if(fullscreen) {
                screen = SDL_SetVideoMode(width, height, colorDepth, SDL_SWSURFACE | SDL_FULLSCREEN);
                lock();
        } else {
                screen = SDL_SetVideoMode(width, height, colorDepth, SDL_HWSURFACE | SDL_HWPALETTE);
        }
        if(screen == NULL) {
                SDL_Quit();
                std::exit(1);
        }

        SDL_WM_SetCaption(title.c_str(), NULL);

        SDL_EnableUNICODE(1);
}


//Locks the screen
void lock(){
        if(SDL_MUSTLOCK(screen))
                if(SDL_LockSurface(screen) < 0)
                        return;
}

//Unlocks the screen
void unlock(){
        if(SDL_MUSTLOCK(screen))
                SDL_UnlockSurface(screen);
}

void redraw()
{
        SDL_UpdateRect(screen, 0, 0, 0, 0);
}

//Clears the screen to black
void cleanScreen()
{
        SDL_FillRect(screen, NULL, 0);
}
