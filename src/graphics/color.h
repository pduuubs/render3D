struct ColorRGB
{
  int r;
  int g;
  int b;

  ColorRGB(int r, int g, int b);
  ColorRGB(const ColorRGB& color);
  ColorRGB();
};

ColorRGB operator/(const ColorRGB& color, int a);
ColorRGB operator*(const ColorRGB& color, int a);
ColorRGB operator+(const ColorRGB& color, const ColorRGB& color2);
ColorRGB operator-(const ColorRGB& color, const ColorRGB& color2);

static const ColorRGB Color_Black    (  0,   0,   0);
static const ColorRGB Color_Red      (255,   0,   0);
static const ColorRGB Color_Green    (  0, 255,   0);
static const ColorRGB Color_Blue     (  0,   0, 255);
static const ColorRGB Color_Cyan     (  0, 255, 255);
static const ColorRGB Color_Magenta  (255,   0, 255);
static const ColorRGB Color_Yellow   (255, 255,   0);
static const ColorRGB Color_White    (255, 255, 255);
static const ColorRGB Color_Gray     (128, 128, 128);
static const ColorRGB Color_Grey     (192, 192, 192);
static const ColorRGB Color_Maroon   (128,   0,   0);
static const ColorRGB Color_Darkgreen(  0, 128,   0);
static const ColorRGB Color_Navy     (  0,   0, 128);
static const ColorRGB Color_Teal     (  0, 128, 128);
static const ColorRGB Color_Purple   (128,   0, 128);
static const ColorRGB Color_Olive    (128, 128,   0);
