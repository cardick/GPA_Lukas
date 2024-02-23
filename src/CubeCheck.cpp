#include "CubeCheck.h"

#include <math.h>
#include "LightCube.h"
#include "Frame.h"
#include "Coloring.h"
#include "Graphics.h"

void CubeCheck::run()
{
    this->testBlockWise();
    this->testLayer();
    this->allOff();
}

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

void CubeCheck::testBlockWise()
{
    Color colors[] = {
        Color(Medium, Off, Off), Color(High, Off, Off), Color(Medium, Off, Off), Color(Off, Off, Off),
        Color(Off, Medium, Off), Color(Off, High, Off), Color(Off, Medium, Off), Color(Off, Off, Off), 
        Color(Off, Off, Medium), Color(Off, Off, High), Color(Off, Off, Medium), Color(Off, Off, Off)
        
    };

    Frame * frame = LightCube::getInstance().getFrame();
    for(int i = 0; i < 16; i++) {
        for(Color c : colors) {
            int startColumn = i * 4;
            frame->setPrepare();
            Graphics::drawColumn(startColumn, c);
            Graphics::drawColumn(startColumn + 1, c);
            Graphics::drawColumn(startColumn + 2, c);
            Graphics::drawColumn(startColumn + 3, c);
            frame->activate(15);
            wait();
        }
    }
}

void CubeCheck::testLayer()
{
    for (int i = 0; i < LightCube::getInstance().getLayerSize(); i++)
    {
        LightCube::getInstance().getFrame()->setPrepare();
        Graphics::drawLayer(i, Color(High, High, High));
        LightCube::getInstance().getFrame()->activate(20);
        wait();
    }   
}

void CubeCheck::allOff()
{
    LightCube::getInstance().getFrame()->reset();
}