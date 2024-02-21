#include "CubeCheck.h"

#include <math.h>
#include "LightCube.h"
#include "Frame.h"
#include "Coloring.h"
#include "Graphics.h"

void CubeCheck::testCubeFunctionality()
{
    uint8_t fadeInOut[] = {Medium, High, Full, High, Medium, Off};
    Color _c =  Color(Off, Off, Off);
    long upperBound = (LightCube::getInstance().getColSize() * LightCube::getInstance().getRowSize()) - 1;
    long rndIndex = random(0, upperBound);

    for (uint8_t i : fadeInOut)
    {
        _c.red = (Brightness) i;
        _c.green = (Brightness) i;
        Graphics::drawColumn(rndIndex, _c, 500);
    }

}

void CubeCheck::allOff()
{
    LightCube::getInstance().getFrame()->reset();
}

void CubeCheck::allOn()
{
    LightCube::getInstance().getFrame()->setAllOn();
}

bool CubeCheck::waitTillEnd()
{
    while(LightCube::getInstance().isIdle()){ 
    // do nothing - just wait
    }
    return true;
}

bool CubeCheck::wait()
{
    while(LightCube::getInstance().isBusy()){ 
    // do nothing - just wait
    }
    return true;
}
