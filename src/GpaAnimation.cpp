#include "GpaAnimation.h"

#include "LightCube.h"
#include "Frame.h"
#include "Coloring.h"
#include "Graphics.h"
#include "Vector.h"
#include "MemoryFree.h"

void GpaAnimation::run()
{
    moveFrontBack();
    moveTunnel();
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

    Serial.println(freeMemory());
    Point3D start = {0, 0, 0};
    SolidColoring coloring = SolidColoring();
    coloring.setColor(Color(High, High, High));

    Frame * f = LightCube::getInstance().getFrame();

    for (int i = 0; i < 15; i++)
    {
        f->setPrepare();
        Graphics::erase();

        // begin frame logic
        start.x = i < 7 ? i : 7;
        start.y = 0;
        start.z = 0;
        Graphics::drawRectangle( &start, Direction::Up, Direction::Left, 8, 8, coloring);

        start.x -= 1;
        if(i<=7 && start.x>=0) {
            Graphics::drawRectangle( &start, Direction::Up, Direction::Left, 8, 8, coloring);
        }

        if (i >= 2)
        {
            start.x = (i - 2) < 7 ? (i - 2) : 7;
            start.y = 1;
            start.z = 1;
            Graphics::drawRectangle(&start, Up, Left, 6, 6, coloring);
            start.x -= 1;
            if(i<=9 && start.x>=0) {
                Graphics::drawRectangle( &start, Direction::Up, Direction::Left, 6, 6, coloring);
            }
        }
        if (i >= 4)
        {
            start.x = (i - 4) < 7 ? (i - 4) : 7;
            start.y = 2;
            start.z = 2;
            Graphics::drawRectangle(&start, Up, Left, 4, 4, coloring);
            start.x -= 1;
            if(i<=11 && start.x>=0) {
                Graphics::drawRectangle( &start, Direction::Up, Direction::Left, 4, 4, coloring);
            }
        }
        if (i >= 6)
        {
            start.x = (i - 6) < 7 ? (i - 6) : 7;
            start.y = 3;
            start.z = 3;
            Graphics::drawRectangle(&start, Up, Left, 2, 2, coloring);
            start.x -= 1;
            if(i <= 13 && start.x>=0) {
                Graphics::drawRectangle( &start, Direction::Up, Direction::Left, 2, 2, coloring);
            }
        }

        // end frame logic
        if(i==0 || i==14) {
            f->activate(getFrameCount(500));
        } else {
            f->activate(getFrameCount(150));
        }

        wait();
    }
    f->reset();
}

void GpaAnimation::moveFrontBack()
{
    SolidColoring coloring = SolidColoring();
    coloring.setColor(Color(High,Off,Medium));

    Frame * f = LightCube::getInstance().getFrame();
    f->setPrepare();
    Graphics::erase();

    for (int i = 0; i < 8; i++)
    {
    
        f->setPrepare();
        Graphics::erase();

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
