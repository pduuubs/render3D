#include <SDL/SDL.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

bool verLine(int x, int y1, int y2, const ColorRGB& color);
void pset(int x, int y, const ColorRGB& color);
void drawBuffer(Uint32* buffer);
