#include "pdubscg.h"

#include <SDL/SDL.h>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>


int w, h;   //Screen WIDTH and HEIGHT


SDL_Surface* screen;
Uint8* inkeys;
SDL_Event event = {0};
std::map<int, bool> keypressed;
//////////////////////////////////////////////////////////////////////////////
//SCREEN RELATED FONCTIONS////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//initialisation of the screen, start the SDL and declare usefull fonctions.

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

////////////////////////////////////////////////////////////////////////////////
//COLOR STRUCTS/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ColorRGB::ColorRGB(Uint8 r, Uint8 g, Uint8 b)
{
        this->r = r;
        this->g = g;
        this->b = b;
}
ColorRGB::ColorRGB(const ColorRGB8bit& color)
{
        this->r = color.r;
        this->g = color.g;
        this->b = color.b;
}
ColorRGB::ColorRGB()
{
        this->r = 0;
        this->g = 0;
        this->b = 0;
}
ColorRGB8bit::ColorRGB8bit(Uint8 r, Uint8 g, Uint8 b)
{
        this->r = r;
        this->g = g;
        this->b = b;
}
ColorRGB8bit::ColorRGB8bit(const ColorRGB& color)
{
        this->r = color.r;
        this->g = color.g;
        this->b = color.b;
}
ColorRGB8bit::ColorRGB8bit()
{
        this->r = 0;
        this->g = 0;
        this->b = 0;
}

//Add two colors
ColorRGB operator+(const ColorRGB& color, const ColorRGB& color2)
{
        ColorRGB c;
        c.r = color.r + color2.r;
        c.g = color.g + color2.g;
        c.b = color.b + color2.b;
        return c;
}

//Subtract two colors
ColorRGB operator-(const ColorRGB& color, const ColorRGB& color2)
{
        ColorRGB c;
        c.r = color.r - color2.r;
        c.g = color.g - color2.g;
        c.b = color.b - color2.b;
        return c;
}

//Multiplies a color with an integer
ColorRGB operator*(const ColorRGB& color, int a)
{
        ColorRGB c;
        c.r = color.r * a;
        c.g = color.g * a;
        c.b = color.b * a;
        return c;
}

//Multiplies a color with an integer
ColorRGB operator*(int a, const ColorRGB& color)
{
        ColorRGB c;
        c.r = color.r * a;
        c.g = color.g * a;
        c.b = color.b * a;
        return c;
}

//Divides a color through an integer
ColorRGB operator/(const ColorRGB& color, int a)
{
        if(a == 0) return color;
        ColorRGB c;
        c.r = color.r / a;
        c.g = color.g / a;
        c.b = color.b / a;
        return c;
}

//Are both colors equal?
bool operator==(const ColorRGB& color, const ColorRGB& color2)
{
        return(color.r == color2.r && color.g == color2.g && color.b == color2.b);
}

//Are both colors not equal?
bool operator!=(const ColorRGB& color, const ColorRGB& color2)
{
        return(!(color.r == color2.r && color.g == color2.g && color.b == color2.b));
}

////////////////////////////////////////////////////////////////////////////////
//GRAPHICAL FONCTIONS///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool verLine(int x, int y1, int y2, const ColorRGB& color)
{
        if(y2 < y1) {y1 += y2; y2 = y1 - y2; y1 -= y2; } //swap y1 and y2
        if(y2 < 0 || y1 >= h  || x < 0 || x >= w) return 0;  //no single point of the line is on screen
        if(y1 < 0) y1 = 0;  //clip
        if(y2 >= w) y2 = h - 1;  //clip

        Uint32 colorSDL = SDL_MapRGB(screen->format, color.r, color.g, color.b);
        Uint32* bufp;

        bufp = (Uint32*)screen->pixels + y1 * screen->pitch / 4 + x;
        for(int y = y1; y <= y2; y++)
        {
                *bufp = colorSDL;
                bufp += screen->pitch / 4;
        }
        return 1;
}

////////////////////////////////////////////////////////////////////////////////
//NON GRAPHICAL FONCTIONS///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

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
