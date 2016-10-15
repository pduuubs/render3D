#include <SDL/SDL.h>

#include "color.h"
#include "screen.h"
#include "render.h"

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

void pset(int x, int y, const ColorRGB& color)
{
        if(x < 0 || y < 0 || x >= w || y >= h) return;
        Uint32 colorSDL = SDL_MapRGB(screen->format, color.r, color.g, color.b);
        Uint32* bufp;
        bufp = (Uint32*)screen->pixels + y * screen->pitch / 4 + x;
        *bufp = colorSDL;
}

void drawBuffer(Uint32* buffer)
{
        Uint32* bufp;
        bufp = (Uint32*)screen->pixels;

        for(int y = 0; y < h; y++)
        {
                for(int x = 0; x < w; x++)
                {
                        *bufp = buffer[y * w + x];
                        bufp++;
                }
                bufp += screen->pitch / 4;
                bufp -= w;
        }
}
