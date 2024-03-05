#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef Coloring_h
#define Coloring_h

#include "Vector.h"

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
public:
    Brightness red;
    Brightness green;
    Brightness blue;
    Color()
    {
        this->red = Off;
        this->green = Off;
        this->blue = Off;
    }

    Color(Brightness red, Brightness green, Brightness blue)
    {
        this->red = red;
        this->green = green;
        this->blue = blue;
    }

    void print() 
    {
        Serial.print(F("color r: "));
        Serial.print(red);
        Serial.print(F(", g: "));
        Serial.print(red);
        Serial.print(F(", b: "));
        Serial.println(red);
    }
};

class Coloring
{
public:
    virtual Color getColor(const Voxel& vox) = 0;
};

class SolidColoring : public Coloring
{
public:
    void setColor(Color c);

    Color getColor(const Voxel& vox);

private:
    Color _c;
};

class ColorSpace : public Coloring
{
public:
    ColorSpace();
    ColorSpace(int width, int depth, int height);
    Color getColor(const Voxel& vox);
    void print();

private:
    int width, depth, height;
    Brightness red(const Voxel& vox);
    Brightness green(const Voxel& vox);
    Brightness blue(const Voxel& vox);
    Brightness colorSpace(const int i);
};

#endif