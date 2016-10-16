#include <SDL/SDL.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

extern int w; //global width
extern int h; //global height

extern SDL_Surface* screen;

void cleanScreen();
void initScreen(int width, int height, bool full, const std::string& text = " ");
void lock();
void unlock();
void redraw();
