#include "GpaAnimation.h"
#include "LightCube.h"
#include "Coloring.h"
#include "Graphics.h"
#include "MemoryFree.h"
#include "Voxel.h"

GpaAnimation::GpaAnimation() : coloring(new SolidColoring())
{
    ((SolidColoring*)coloring)->setColor(Color(High, High, High));
}

GpaAnimation::~GpaAnimation()
{
    delete coloring;
}

void GpaAnimation::run()
{
    Serial.print(F("Color red "));
    Serial.print(coloring->getColor(0,0,0).red, BIN);
    Serial.print(F(", green "));
    Serial.print(coloring->getColor(0,0,0).green, BIN);
    Serial.print(F(", blue "));
    Serial.println(coloring->getColor(0,0,0).blue, BIN);
    memFree();
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
    Voxel start = Voxel();
    wait();

    for (int i = 0; i < 15; i++)
    {
        // set prepare to indicate frame state will change
        LightCube::getInstance().getFrame()->setPrepare();

        // clean up screen before modifying
        Graphics::erase();

        // begin frame logic
        drawFTB(start, i, 8);

        if (i >= 2)
        {
            drawFTB(start, i, 6);
        }
        if (i >= 4)
        {
            drawFTB(start, i, 4);
        }
        if (i >= 6)
        {
            drawFTB(start, i, 2);
        }

        // end frame logic
        if (i == 0 || i == 14)
        {
            LightCube::getInstance().getFrame()->activate(getFrameCount(250));
        }
        else
        {
            LightCube::getInstance().getFrame()->activate(getFrameCount(90));
        }

        wait();
    }
}

void GpaAnimation::moveTunnelBack()
{
    // reverse movement for move tunnel
    Voxel start = Voxel();
    wait();

    for (int i = 15; i >= 0; i--)
    {
        LightCube::getInstance().getFrame()->setPrepare();
        LightCube::getInstance().getFrame()->setAllOff();

        drawBTF(start, i, 8);
        drawBTF(start, i, 6);
        drawBTF(start, i, 4);
        drawBTF(start, i, 2);

        if (i == 0)
        {
            LightCube::getInstance().getFrame()->activate(getFrameCount(500));
        }
        else
        {
            LightCube::getInstance().getFrame()->activate(getFrameCount(90));
        }
        wait();
    }
}

void GpaAnimation::drawFTB(Voxel vox, uint8_t step, uint8_t size)
{
    vox.x = (step - 8 + size) < 7 ? (step - 8 + size) : 7;
    vox.y = (8 - size) / 2;
    vox.z = (8 - size) / 2;

    Graphics::drawRectangle(&vox, Up, Left, size, size, *coloring, LightCube::getInstance().getFrame());
    vox.x -= 1;
    if (step <= (15 - size) && vox.x >= 0)
    {
        Graphics::drawRectangle(&vox, Direction::Up, Direction::Left, size, size, *coloring, LightCube::getInstance().getFrame());
    }
}

void GpaAnimation::drawBTF(Voxel vox, int8_t step, uint8_t size)
{
    vox.x = step <= size ? 0 : (step <= 7 + size ? step - size : 7);
    vox.y = (8 - size) / 2;
    vox.z = (8 - size) / 2;

    if (step > ((size - 3) < 0 ? 0 : size - 3))
    {
        Graphics::drawRectangle(&vox, Direction::Up, Direction::Left, size, size, *coloring, LightCube::getInstance().getFrame());
    }
    if (step < 8 + size && step > size - 1)
    {
        vox.x += 1;
        Graphics::drawRectangle(&vox, Direction::Up, Direction::Left, size, size, *coloring, LightCube::getInstance().getFrame());
    }
}