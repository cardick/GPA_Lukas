#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef ColorSpectrum_h
#define ColorSpectrum_h

#include "Animation.h"
#include "Coloring.h"

class ColorSpectrum : public Animation
{
private:
    ColorSpace *space;
public:
    ColorSpectrum();
    ~ColorSpectrum();
    void run();
};

#endif