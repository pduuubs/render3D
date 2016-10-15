#include <SDL/SDL.h>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

Uint8* inkeys;
SDL_Event event = {0};
std::map<int, bool> keypressed;

unsigned long getTicks()
{
        return SDL_GetTicks();
}

void readKeys()
{
        SDL_PollEvent(&event);
        inkeys = SDL_GetKeyState(NULL);
}

bool keyDown(int key) //this checks if the key is held down, returns true all the time until the key is up
{
        return (inkeys[key] != 0);
}
