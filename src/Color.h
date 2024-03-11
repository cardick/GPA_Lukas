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

inline Brightness operator|(Brightness a, Brightness b)
{
    return static_cast<Brightness>(static_cast<int>(a) | static_cast<int>(b));
}

/**
 * Color struct holds the brightness for each LED color.
 */
class Color
{
public:
    Brightness red;
    Brightness green;
    Brightness blue;
    
    Color() : red(Off), green(Off), blue(Off)
    {
    }

    Color(Brightness red, Brightness green, Brightness blue) : red(red), green(green), blue(blue)
    {
    }

    Color &operator=(const Color &a) {
        red = a.red;
        green = a.green;
        blue = a.blue;
        return *this;
    }

    void print() const
    {
        Serial.print(F("color r: "));
        Serial.print(red);
        Serial.print(F(", g: "));
        Serial.print(red);
        Serial.print(F(", b: "));
        Serial.println(red);
    }

    static Brightness toBrightness(uint8_t value) 
    {
        if(value == 0) 
        {
            return Off;
        }

        Brightness tmp;
        if((value & Low) == Low) {
            tmp = Low;
        }
        if((value & Medium) == Medium) {
            tmp = Medium;
        }
        if((value & High) == High) {
            tmp = High;
        }
        if((value & Full) == Full) {
            return Full;
        }
        return tmp;
    }
};

#endif