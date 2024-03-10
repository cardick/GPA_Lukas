#include "GpaAnimation.h"

#include "LightCube.h"
#include "Frame.h"
#include "Coloring.h"
#include "Graphics.h"
#include "Vector.h"
#include "MemoryFree.h"

void GpaAnimation::run()
{
    SolidColoring coloring = SolidColoring();
    coloring.setColor(Color(High, High, High));
    run(2000, &coloring);
}

void GpaAnimation::run(unsigned long millis, Coloring* coloring)
{
    LightCube::getInstance().reset();
    wait();

    unsigned long current = currentMillis();
    while (currentMillis()-current < millis )
    {
        moveTunnel(LightCube::getInstance().getFrame(), coloring);
        moveTunnelBack(LightCube::getInstance().getFrame(), coloring);
    }
}

void GpaAnimation::moveTunnel(Frame *frame, Coloring* coloring)
{
    // was möchte ich, das der Würfel tut
    // Die hinterste Matrix bekommt einen aussen rahmen der dann nach zeit(x) um eine Matrix nach vorne rückt.
    // die jetzt hintere matrix wird dann mit einem um eine reihe engerem rahmen (ausgefült)
    // dann wird wieder nach zeit(x) weitergefürt. bis die erste matrix also der außen rahmen an der fordesten Matrix ist,
    // dann geht der äussere rahmen aus und der zweite rahmen geht an die erste matrix und
    // das ganze geht dann so bis die ganz enge Matrix ganz vorne ist
    // dann könnte die erste Matrix komplett weiß werden und die ganze animation fängt von vorne an.
    Voxel start = Voxel();

    for (int i = 0; i < 15; i++)
    {
        // set prepare to indicate frame state will change
        frame->setPrepare();

        // clean up screen before modifying
        Graphics::erase();

        // begin frame logic
        start.x = i < 7 ? i : 7;
        start.y = 0;
        start.z = 0;
        Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 8, 8, *coloring, frame);

        start.x -= 1;
        if (i <= 7 && start.x >= 0)
        {
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 8, 8, *coloring, frame);
        }

        if (i >= 2)
        {
            start.x = (i - 2) < 7 ? (i - 2) : 7;
            start.y = 1;
            start.z = 1;
            Graphics::drawRectangle(&start, Up, Left, 6, 6, *coloring, frame);
            start.x -= 1;
            if (i <= 9 && start.x >= 0)
            {
                Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 6, 6, *coloring, frame);
            }
        }
        if (i >= 4)
        {
            start.x = (i - 4) < 7 ? (i - 4) : 7;
            start.y = 2;
            start.z = 2;
            Graphics::drawRectangle(&start, Up, Left, 4, 4, *coloring, frame);
            start.x -= 1;
            if (i <= 11 && start.x >= 0)
            {
                Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 4, 4, *coloring, frame);
            }
        }
        if (i >= 6)
        {
            start.x = (i - 6) < 7 ? (i - 6) : 7;
            start.y = 3;
            start.z = 3;
            Graphics::drawRectangle(&start, Up, Left, 2, 2, *coloring, frame);
            start.x -= 1;
            if (i <= 13 && start.x >= 0)
            {
                Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 2, 2, *coloring, frame);
            }
        }

        // end frame logic
        if (i == 0 || i == 14)
        {
            frame->activate(getFrameCount(250));
        }
        else
        {
            frame->activate(getFrameCount(90));
        }

        wait();
    }
}

void GpaAnimation::moveTunnelBack(Frame *frame, Coloring* coloring)
{
    // laufe zurück Umkehrfunktion zu moveTunnel
    wait();

    Voxel start = Voxel();

    SolidColoring offColoring = SolidColoring();
    offColoring.setColor(Color(Off, Off, Off));

    int offset = 8;

    for (int i = 7 + offset; i >= 0; i--)
    {
        frame->setPrepare();
        frame->setAllOff();

        start.x = i <= offset ? 0 : i - offset;
        start.y = 0;
        start.z = 0;

        if (i > offset - 3)
        {
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 8, 8, *coloring, frame);
        }
        if (i > offset - 1)
        {
            start.x += 1;
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 8, 8, *coloring, frame);
        }

        start.x = i <= offset - 2 ? 0 : i <= offset + 5 ? i - offset + 2 : 7;
        start.y = 1;
        start.z = 1;

        if (i > offset - 5)
        {
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 6, 6, *coloring, frame);
        }
        if (i < offset + 6 && i > offset - 3)
        {
            start.x += 1;
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 6, 6, *coloring, frame);
        }

        start.x = i <= offset - 4 ? 0 : i <= offset + 3 ? i - offset + 4 : 7;
        start.y = 2;
        start.z = 2;

        if (i > offset - 7)
        {
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 4, 4, *coloring, frame);
        }
        if (i < offset + 4 && i > offset - 5)
        {
            start.x += 1;
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 4, 4, *coloring, frame);
        }

        start.x = i <= offset - 6 ? 0 : i <= offset + 1 ? i - offset + 6 : 7;
        start.y = 3;
        start.z = 3;
        
        if (i > 0)
        {
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 2, 2, *coloring, frame);
        }
        if (i <= offset + 3 && i > offset - 7)
        {
            start.x += 1;
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 2, 2, *coloring, frame);
        }

        if (i == 0)
        {
            frame->activate(getFrameCount(500));
        }
        else
        {
            frame->activate(getFrameCount(90));
        }
        wait();
    }
}

unsigned long GpaAnimation::currentMillis()
{
    return millis();
}
