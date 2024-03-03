#include "GpaAnimation.h"

#include "LightCube.h"
#include "Frame.h"
#include "Coloring.h"
#include "Graphics.h"
#include "Vector.h"
#include "MemoryFree.h"

void GpaAnimation::run()
{
    run(2000);
}

void GpaAnimation::run(long millis)
{
    LightCube::getInstance().reset();
    wait();

    unsigned long current = currentMillis();
    while (currentMillis()-current < millis )
    {
        moveTunnel(LightCube::getInstance().getFrame());
        moveTunnelBack(LightCube::getInstance().getFrame());
    }
    
}

void GpaAnimation::moveTunnel(Frame *frame)
{
    // was möchte ich, das der Würfel tut
    // Die hinterste Matrix bekommt einen aussen rahmen der dann nach zeit(x) um eine Matrix nach vorne rückt.
    // die jetzt hintere matrix wird dann mit einem um eine reihe engerem rahmen (ausgefült)
    // dann wird wieder nach zeit(x) weitergefürt. bis die erste matrix also der außen rahmen an der fordesten Matrix ist,
    // dann geht der äussere rahmen aus und der zweite rahmen geht an die erste matrix und
    // das ganze geht dann so bis die ganz enge Matrix ganz vorne ist
    // dann könnte die erste Matrix komplett weiß werden und die ganze animation fängt von vorne an.
    Point3D start = {0, 0, 0};
    SolidColoring coloring = SolidColoring();
    coloring.setColor(Color(High, High, High));

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
        Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 8, 8, coloring, frame);

        start.x -= 1;
        if (i <= 7 && start.x >= 0)
        {
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 8, 8, coloring, frame);
        }

        if (i >= 2)
        {
            start.x = (i - 2) < 7 ? (i - 2) : 7;
            start.y = 1;
            start.z = 1;
            Graphics::drawRectangle(&start, Up, Left, 6, 6, coloring, frame);
            start.x -= 1;
            if (i <= 9 && start.x >= 0)
            {
                Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 6, 6, coloring, frame);
            }
        }
        if (i >= 4)
        {
            start.x = (i - 4) < 7 ? (i - 4) : 7;
            start.y = 2;
            start.z = 2;
            Graphics::drawRectangle(&start, Up, Left, 4, 4, coloring, frame);
            start.x -= 1;
            if (i <= 11 && start.x >= 0)
            {
                Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 4, 4, coloring, frame);
            }
        }
        if (i >= 6)
        {
            start.x = (i - 6) < 7 ? (i - 6) : 7;
            start.y = 3;
            start.z = 3;
            Graphics::drawRectangle(&start, Up, Left, 2, 2, coloring, frame);
            start.x -= 1;
            if (i <= 13 && start.x >= 0)
            {
                Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 2, 2, coloring, frame);
            }
        }

        // end frame logic
        if (i == 0 || i == 14)
        {
            frame->activate(getFrameCount(250));
        }
        else
        {
            frame->activate(getFrameCount(100));
        }

        wait();
    }
}

void GpaAnimation::moveTunnelBack(Frame *frame)
{
    // laufe zurück Umkehrfunktion zu moveTunnel
    wait();

    Point3D start = {0, 0, 0};
    SolidColoring coloring = SolidColoring();
    coloring.setColor(Color(High, High, High));

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
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 8, 8, coloring, frame);
        }
        if (i > offset - 1)
        {
            start.x += 1;
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 8, 8, coloring, frame);
        }

        start.x = i <= offset - 2 ? 0 : i <= offset + 5 ? i - offset + 2
                                                        : 7;
        start.y = 1;
        start.z = 1;
        if (i > offset - 5)
        {
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 6, 6, coloring, frame);
        }
        if (i < offset + 6 && i > offset - 3)
        {
            start.x += 1;
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 6, 6, coloring, frame);
        }

        start.x = i <= offset - 4 ? 0 : i <= offset + 3 ? i - offset + 4
                                                        : 7;
        start.y = 2;
        start.z = 2;

        if (i > offset - 7)
        {
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 4, 4, coloring, frame);
        }
        if (i < offset + 4 && i > offset - 5)
        {
            start.x += 1;
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 4, 4, coloring, frame);
        }

        start.x = i <= offset - 6 ? 0 : i <= offset + 1 ? i - offset + 6
                                                        : 7;
        start.y = 3;
        start.z = 3;
        if (i > 0)
        {
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 2, 2, coloring, frame);
        }
        if (i <= offset + 3 && i > offset - 7)
        {
            start.x += 1;
            Graphics::drawRectangle(&start, Direction::Up, Direction::Left, 2, 2, coloring, frame);
        }

        if (i == 0)
        {
            frame->activate(getFrameCount(500));
        }
        else
        {
            frame->activate(getFrameCount(100));
        }
        wait();
    }
}

void GpaAnimation::snake(long millis)
{
    Point3D p = Point3D(random(0, 7), random(0, 7), random(0, 7));
    Vector3D vec = Vector3D(1, 1, 1);

    for (int i = 0; i < 10; i++)
    {
        int mycase = random(0, 45);
        switch (0) // mycase%3)
        {
        case 0:
            moveForward(&p, &vec, mycase % 8);
            break;
        case 1:
            changeDir(&p, Up, 0);
            break;
        default:
            makeLoop(&p);
            break;
        }
    }
}

void GpaAnimation::changeDir(Point3D *p, const Direction dir, const int steps)
{
}

void GpaAnimation::moveForward(Point3D *p, const Vector3D *v, int steps)
{
    Point3D tmp;
    for (int i = 0; i < steps; i++)
    {
        tmp.x = p->x;
        tmp.y = p->y;
        tmp.z = p->z;
        *p += *v;
        LightCube::getInstance().getFrame()->setPrepare();
        memFree();
        if (isInBoundary(p))
        {
            LightCube::getInstance().getFrame()->set(p->x, p->y, p->z, Full, Off, Full);
            LightCube::getInstance().getFrame()->set(tmp.x, tmp.y, tmp.z, Off, Off, Off);
        }
       // if(LightCube::getInstance().getFrame()->isPrepare()) {
            LightCube::getInstance().getFrame()->activate(getFrameCount(200));
        // }
        wait();
    }
}

void GpaAnimation::makeLoop(Point3D *p)
{
}

bool GpaAnimation::isPossibleDirection(const Vector3D *vec)
{
    return false;
}

bool GpaAnimation::isInBoundary(const Point3D *p)
{
    if (p->x < 0 || p->x > 8)
        return false;
    if (p->y < 0 || p->y > 8)
        return false;
    if (p->z < 0 || p->z > 8)
        return false;
    return false;
}

unsigned long GpaAnimation::currentMillis()
{
    return millis();
}
