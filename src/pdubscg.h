#include <SDL/SDL.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

extern int w; //global width
extern int h; //global height

//////////////////////////////////////////////////////////////////////////////
//SCREEN RELATED FONCTIONS////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void cleanScreen();
void initScreen(int width, int height, bool full, const std::string& text = " ");
void lock();
void unlock();
void redraw();


////////////////////////////////////////////////////////////////////////////////
//COLOR STRUCTS/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

struct ColorRGB8bit;
//a color with 3 components: r, g and b
struct ColorRGB
{
  int r;
  int g;
  int b;

  ColorRGB(int r, int g, int b);
  ColorRGB(const ColorRGB8bit& color);
  ColorRGB();
};

ColorRGB operator+(const ColorRGB& color, const ColorRGB& color2);
ColorRGB operator-(const ColorRGB& color, const ColorRGB& color2);
ColorRGB operator*(const ColorRGB& color, int a);
ColorRGB operator*(int a, const ColorRGB& color);
ColorRGB operator/(const ColorRGB& color, int a);
bool operator==(const ColorRGB& color, const ColorRGB& color2);
bool operator!=(const ColorRGB& color, const ColorRGB& color2);

//a color with 3 components: r, g and b
struct ColorRGB8bit
{
  int r;
  int g;
  int b;

  ColorRGB8bit(int r, int g, int b);
  ColorRGB8bit(const ColorRGB& color);
  ColorRGB8bit();
};

static const ColorRGB RGB_Black    (  0,   0,   0);
static const ColorRGB RGB_Red      (255,   0,   0);
static const ColorRGB RGB_Green    (  0, 255,   0);
static const ColorRGB RGB_Blue     (  0,   0, 255);
static const ColorRGB RGB_Cyan     (  0, 255, 255);
static const ColorRGB RGB_Magenta  (255,   0, 255);
static const ColorRGB RGB_Yellow   (255, 255,   0);
static const ColorRGB RGB_White    (255, 255, 255);
static const ColorRGB RGB_Gray     (128, 128, 128);
static const ColorRGB RGB_Grey     (192, 192, 192);
static const ColorRGB RGB_Maroon   (128,   0,   0);
static const ColorRGB RGB_Darkgreen(  0, 128,   0);
static const ColorRGB RGB_Navy     (  0,   0, 128);
static const ColorRGB RGB_Teal     (  0, 128, 128);
static const ColorRGB RGB_Purple   (128,   0, 128);
static const ColorRGB RGB_Olive    (128, 128,   0);

////////////////////////////////////////////////////////////////////////////////
//GRAPHICAL FONCTIONS///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool verLine(int x, int y1, int y2, const ColorRGB& color);

////////////////////////////////////////////////////////////////////////////////
//NON GRAPHICAL FONCTIONS///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

unsigned long getTicks();
void readKeys();
bool keyDown(int key) ;
