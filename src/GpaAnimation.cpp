#include "GpaAnimation.h"
#include "LightCube.h"
#include "Coloring.h"
#include "Graphics.h"
#include "MemoryFree.h"

GpaAnimation::GpaAnimation() : coloring(new SolidColoring())
{
    ((SolidColoring*)coloring)->setColor(Color(High, High, High));
}

GpaAnimation::~GpaAnimation()
{
    delete coloring;
    coloring = nullptr;
}

void GpaAnimation::run()
{
    moveTunnel();
    moveTunnelBack();
}

void GpaAnimation::run(unsigned long runtime, Coloring *coloring)
{
    this->coloring = coloring;
    unsigned long current = millis();
    while (millis() - current < runtime)
    {
        moveTunnel();
        moveTunnelBack();
    }
}

void GpaAnimation::moveTunnel()
{
    // was möchte ich, das der Würfel tut
    // Die hinterste Matrix bekommt einen aussen rahmen der dann nach zeit(x) um eine Matrix nach vorne rückt.
    // die jetzt hintere matrix wird dann mit einem um eine reihe engerem rahmen (ausgefült)
    // dann wird wieder nach zeit(x) weitergefürt. bis die erste matrix also der außen rahmen an der fordesten Matrix ist,
    // dann geht der äussere rahmen aus und der zweite rahmen geht an die erste matrix und
    // das ganze geht dann so bis die ganz enge Matrix ganz vorne ist
    // dann könnte die erste Matrix komplett weiß werden und die ganze animation fängt von vorne an.
    wait();

    for (int i = 0; i < 15; i++)
    {
        // set prepare to indicate frame state will change
        LightCube::getInstance().getFrame()->setPrepare();

        // clean up screen before modifying
        Graphics::erase();

        // begin frame logic
        drawFTB(i, 8);

        if (i >= 2)
        {
            drawFTB(i, 6);
        }
        if (i >= 4)
        {
            drawFTB(i, 4);
        }
        if (i >= 6)
        {
            drawFTB(i, 2);
        }

        // end frame logic
        if (i == 0 || i == 14)
        {
            LightCube::getInstance().getFrame()->activate(getFrameCount(250));
        }
        else
        {
            LightCube::getInstance().getFrame()->activate(getFrameCount(80));
        }

        wait();
    }
}

void GpaAnimation::moveTunnelBack()
{
    // reverse movement for move tunnel
    wait();

    for (int i = 15; i >= 0; i--)
    {
        LightCube::getInstance().getFrame()->setPrepare();
        LightCube::getInstance().getFrame()->setAllOff();

        drawBTF(i, 8);
        drawBTF(i, 6);
        drawBTF(i, 4);
        drawBTF(i, 2);

        if (i == 0)
        {
            LightCube::getInstance().getFrame()->activate(getFrameCount(500));
        }
        else
        {
            LightCube::getInstance().getFrame()->activate(getFrameCount(80));
        }
        wait();
    }
}

void GpaAnimation::drawFTB(uint8_t step, uint8_t size)
{
    uint8_t px = (step - 8 + size) < 7 ? (step - 8 + size) : 7;
    uint8_t py = (8 - size) / 2;
    uint8_t pz = (8 - size) / 2;

    Graphics::drawRectangle(px, py, pz, Up, Left, size, size, *coloring, LightCube::getInstance().getFrame());
    if (step <= (15 - size) && px >= 0)
    {
        Graphics::drawRectangle(px+1, py, pz, Up, Left, size, size, *coloring, LightCube::getInstance().getFrame());
    }
}

void GpaAnimation::drawBTF(int8_t step, uint8_t size)
{
    uint8_t px = step <= size ? 0 : (step <= 7 + size ? step - size : 7);
    uint8_t py = (8 - size) / 2;
    uint8_t pz = (8 - size) / 2;

    if (step > ((size - 3) < 0 ? 0 : size - 3))
    {
        Graphics::drawRectangle(px, py, pz, Up, Left, size, size, *coloring, LightCube::getInstance().getFrame());
    }
    if (step < 8 + size && step > size - 1)
    {
        Graphics::drawRectangle(px+1, py, pz, Up, Left, size, size, *coloring, LightCube::getInstance().getFrame());
    }
}