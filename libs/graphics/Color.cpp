#include "color.h"

ColorRGB::ColorRGB(int r, int g, int b)
{
        this->r = r;
        this->g = g;
        this->b = b;
}

ColorRGB::ColorRGB()
{
        this->r = 0;
        this->g = 0;
        this->b = 0;
}
ColorRGB::ColorRGB(const ColorRGB& color)
{
        this->r = color.r;
        this->g = color.g;
        this->b = color.b;
}
ColorRGB operator*(const ColorRGB& color, int a)
{
        ColorRGB c;
        c.r = color.r * a;
        c.g = color.g * a;
        c.b = color.b * a;
        return c;
}

ColorRGB operator/(const ColorRGB& color, int a)
{
        if(a == 0) return color;
        ColorRGB c;
        c.r = color.r / a;
        c.g = color.g / a;
        c.b = color.b / a;
        return c;
}

ColorRGB operator+(const ColorRGB& color, const ColorRGB& color2)
{
        ColorRGB c;
        c.r = color.r + color2.r;
        c.g = color.g + color2.g;
        c.b = color.b + color2.b;
        return c;
}

ColorRGB operator-(const ColorRGB& color, const ColorRGB& color2)
{
        ColorRGB c;
        c.r = color.r - color2.r;
        c.g = color.g - color2.g;
        c.b = color.b - color2.b;
        return c;
}
