#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef Coloring_h
#define Coloring_h

/**
 * Brightness flags enabling a 4 Bit BAM (Bit Angle Manipulation).
 */
enum Brightness
{
    Off = 0b0 << 0,
    Low = 0b1 << 0,
    Medium = 0b11 << 0,
    High = 0b111 << 0,
    Full = 0b1111 << 0
};

/**
 * Color struct holds the brightness for each LED color.
 */
struct Color
{
    Brightness red;
    Brightness green;
    Brightness blue;

    Color(Brightness red, Brightness green, Brightness blue) {
        this->red = red;
        this->green = green;
        this->blue = blue;
    }
};

class Coloring {
    public:
        virtual Color getColor() = 0;
    protected:

};

class SolidColoring : public Coloring {

    public:
        Color getColor();
};

#endif