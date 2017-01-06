#ifndef IVY_COLOR_H
#define IVY_COLOR_H

#include "Symbols.h"

struct IVY_API Color {
    static const Color CornflowerBlue;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Black;
    static const Color Magenta;
    static const Color Purple;
    static const Color White;
    static const Color Yellow;

    Color() { *this = Black; }

    Color(float red, float green, float blue, float alpha) {
        this->m_Red = red;
        this->m_Green = green;
        this->m_Blue = blue;
        this->m_Alpha = alpha;
    }

    float GetRedChannel(void) const { return m_Red; }
    float GetGreenChannel(void) const { return m_Green; }
    float GetBlueChannel(void) const { return m_Blue; }
    float GetAlphaChannel(void) const { return m_Alpha; }

private:

    float m_Red;
    float m_Green;
    float m_Blue;
    float m_Alpha;
};

#endif // IVY_COLOR_H