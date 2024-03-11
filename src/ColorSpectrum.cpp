#include "ColorSpectrum.h"
#include "Coloring.h"

ColorSpectrum::ColorSpectrum() : space(new ColorSpace(8,8,8))
{
}

ColorSpectrum::~ColorSpectrum()
{
    delete space;
}

void ColorSpectrum::run()
{
    wait();

    // spanning the color space
    LightCube::getInstance().getFrame()->setPrepare();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                Color color = space->getColor(static_cast<uint8_t>(i), static_cast<uint8_t>(j), static_cast<uint8_t>(k));
                LightCube::getInstance().getFrame()->set(i, j, k, color.red, color.green, color.blue);
            }
        }
    }
    
    LightCube::getInstance().getFrame()->activate(getFrameCount(500));
    wait();
}