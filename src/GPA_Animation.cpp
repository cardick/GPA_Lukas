#include "GPA_Animation.h"

#include "LightCube.h"
#include "Frame.h"
#include "Coloring.h"
#include "Graphics.h"
#include "Vector.h"

void GpaAnimation::run()
{
    // start coding here

    // was möchte ich, das der Würfel tut

    // Die hinterste Matrix bekommt einen aussen rahmen der dann nach zeit(x) um eine Matrix nach vorne rückt.

    // prepare frame

    // drawRectangle - outer lines is Point3D(0,0,0), drirectionA = Up, directionB = Right, lengthA = 8, lengthB = 8

    // getFrameCount(200);
    // activate frame
    // wait();

    // die jetzt hintere matrix wird dann mit einem um eine reihe engerem rahmen (ausgefült)
    // dann wird wieder nach zeit(x) weitergefürt. bis die erste matrix also der außen rahmen an der fordesten Matrix ist,
    // dann geht der äussere rahmen aus und der zweite rahmen geht an die erste matrix und
    // das ganze geht dann so bis die ganz enge Matrix ganz vorne ist
    // dann könnte die erste Matrix komplett weiß werden und die ganze animation fängt von vorne an.
    Point3D start = {0, 0, 0};
    SolidColoring *coloring = new SolidColoring();
    coloring->setColor(Color(High, High, High));

    for (int i = 0; i < 14; i++)
    {
        LightCube::getInstance().getFrame()->setPrepare();
        Graphics::erase();

        // begin frame logic
        start.x = 0;
        start.y = min(i, 7);
        Graphics::drawRectangle(start, Up, Left, 8, 8, coloring);

        if (i >= 2)
        {
            start.x = 1;
            start.y = min(i - 2, 7);
            Graphics::drawRectangle(start, Up, Left, 8 - 2, 8 - 2, coloring);
        }
        if (i >= 4)
        {
            start.x = 2;
            start.y = min(i - 4, 7);
            Graphics::drawRectangle(start, Up, Left, 8 - 4, 8 - 4, coloring);
        }
        if (i >= 6)
        {
            start.x = 3;
            start.y = min(i - 6, 7);
            Graphics::drawRectangle(start, Up, Left, 8 - 6, 8 - 6, coloring);
        }

        // end frame logic
        LightCube::getInstance().getFrame()->activate(getFrameCount(500));
        wait();
    }
}
