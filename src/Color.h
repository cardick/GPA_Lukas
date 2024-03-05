#include <Arduino.h>
#ifndef Color_h
#define Color_h

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
class Color
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

#endif