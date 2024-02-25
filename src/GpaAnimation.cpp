#include "GpaAnimation.h"

#include "LightCube.h"
#include "Frame.h"
#include "Coloring.h"
#include "Graphics.h"
#include "Vector.h"
#include "MemoryFree.h"

void GpaAnimation::run()
{
    Point3D start = {0,0,0};
    SolidColoring coloring = SolidColoring();
    coloring.setColor(Color(High,Off,Medium));

    Frame * f = LightCube::getInstance().getFrame();

    for (int i = 0; i < 8; i++)
    {
    
        f->setPrepare();
        Graphics::erase();
        //Graphics::drawRectangle( &start, Direction::Left, Direction::Up, 6, 6, coloring);
        LightCube::getInstance().getFrame()->set(i,1,1,High,Medium,Off);
        LightCube::getInstance().getFrame()->set(i,1,2,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,1,3,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,1,4,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,1,5,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,1,6,High,Medium,Off);

        LightCube::getInstance().getFrame()->set(i,2,1,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,3,1,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,4,1,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,5,1,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,6,1,High,Medium,Off);

        LightCube::getInstance().getFrame()->set(i,6,2,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,6,3,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,6,4,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,6,5,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,6,6,High,Medium,Off);

        LightCube::getInstance().getFrame()->set(i,2,6,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,3,6,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,4,6,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,5,6,High,Off,Medium);

        LightCube::getInstance().getFrame()->set(i,3,3,High,Medium,Medium);
        LightCube::getInstance().getFrame()->set(i,3,4,High,Medium,Medium);
        LightCube::getInstance().getFrame()->set(i,4,3,High,Medium,Medium);
        LightCube::getInstance().getFrame()->set(i,4,4,High,Medium,Medium);

        if(i==0 || i==7) {
            f->activate(getFrameCount(500));
        } else {
            f->activate(getFrameCount(100));
        }
        wait();
    }
    
    for (int i = 6; i >= 0; i--)
    {
        f->setPrepare();
        Graphics::erase();
        //Graphics::drawRectangle( &start, Direction::Left, Direction::Up, 6, 6, coloring);
        LightCube::getInstance().getFrame()->set(i,1,1,High,Medium,Off);
        LightCube::getInstance().getFrame()->set(i,1,2,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,1,3,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,1,4,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,1,5,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,1,6,High,Medium,Off);

        LightCube::getInstance().getFrame()->set(i,2,1,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,3,1,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,4,1,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,5,1,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,6,1,High,Medium,Off);

        LightCube::getInstance().getFrame()->set(i,6,2,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,6,3,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,6,4,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,6,5,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,6,6,High,Medium,Off);

        LightCube::getInstance().getFrame()->set(i,2,6,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,3,6,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,4,6,High,Off,Medium);
        LightCube::getInstance().getFrame()->set(i,5,6,High,Off,Medium);

        LightCube::getInstance().getFrame()->set(i,3,3,High,Medium,Medium);
        LightCube::getInstance().getFrame()->set(i,3,4,High,Medium,Medium);
        LightCube::getInstance().getFrame()->set(i,4,3,High,Medium,Medium);
        LightCube::getInstance().getFrame()->set(i,4,4,High,Medium,Medium);

        if(i==0) {
            f->activate(getFrameCount(500));
        } else {
            f->activate(getFrameCount(100));
        }
        wait();
    }
    

    f->reset();
}

void GpaAnimation::doIt() 
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
    Serial.println(freeMemory());
    Point3D start = {0, 0, 0};
    SolidColoring coloring = SolidColoring();
    coloring.setColor(Color(High, High, High));
    // Serial.println("Begin animation");

    for (int i = 0; i < 14; i++)
    {
        // Serial.print("loop ");
        // Serial.println(i);

        LightCube::getInstance().getFrame()->setPrepare();
        Graphics::erase();
        // begin frame logic
        start.x = 0;
        start.y = i < 7 ? i : 7;
        Graphics::drawRectangle( &start, Direction::Up, Direction::Left, 8, 8, coloring);

        if (i >= 2)
        {
            start.x = 1;
            start.y = (i - 2) < 7 ? (i - 2) : 7;
            Graphics::drawRectangle(&start, Up, Left, 8 - 2, 8 - 2, coloring);
        }
        if (i >= 4)
        {
            start.x = 2;
            start.y = (i - 4) < 7 ? (i - 4) : 7;
            Graphics::drawRectangle(&start, Up, Left, 8 - 4, 8 - 4, coloring);
        }
        if (i >= 6)
        {
            start.x = 3;
            start.y = (i - 6) < 7 ? (i - 6) : 7;
            Graphics::drawRectangle(&start, Up, Left, 8 - 6, 8 - 6, coloring);
        }

        // end frame logic
        LightCube::getInstance().getFrame()->activate(getFrameCount(500));
        wait();
        // Serial.print("mem free ");
        // Serial.println(freeMemory());
    }
}
