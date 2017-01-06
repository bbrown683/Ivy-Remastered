#ifndef IVYCOLOR_H
#define IVYCOLOR_H

#include "ivySymbols.h"

struct IVY_API ivyColor
{
    static const ivyColor CornflowerBlue;
    static const ivyColor Red;
    static const ivyColor Green;
    static const ivyColor Blue;
    static const ivyColor Black;
    static const ivyColor Magenta;
    static const ivyColor Purple;
    static const ivyColor White;
    static const ivyColor Yellow;

    ivyColor()
    {
        *this = White;
    }

    ivyColor(float red, float green, float blue, float alpha)
    {
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->alpha = alpha;
    }

    float GetRed() const
    {
        return red;
    }

    float GetGreen() const
    {
        return green;
    }

    float GetBlue() const
    {
        return blue;
    }

    float GetAlpha() const
    {
        return alpha;
    }

private:

    float red;
    float green;
    float blue;
    float alpha;
};

#endif