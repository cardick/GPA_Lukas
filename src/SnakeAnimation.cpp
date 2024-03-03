#include "SnakeAnimation.h"
#include "Coloring.h"
#include "Vector.h"

void SnakeAnimation::run()
{
    LightCube::getInstance().getFrame()->setAllOff();
    LightCube::getInstance().getFrame()->activate(1);
    wait();

    Point3D p = Point3D(random(100) % 8, random(100) % 8, random(100) % 8);

    Vector3D vec = Vector3D();

    for (int i = 0; i < 50; i++)
    {
        Vector::setDirection(&vec, randomDirection());

        // @todo: get new directory as long as random direction is not possible

        // @todo: get random action for the snake
        switch (0)
        {
        case 0:
            moveForward(&p, &vec, min(3, random(100) % 8));
            break;
        case 1:
            changeDirAndMoveForward(&p, &vec, 0);
            break;
        default:
            makeLoop(&p);
            break;
        }
    }
}

void SnakeAnimation::moveForward(Point3D *p, const Vector3D *v, int steps)
{
    Point3D tmp = Point3D();
    for (int i = 0; i < steps; i++)
    {
        Frame *f = LightCube::getInstance().getFrame();
        if (f->canPrepare())
        {
            f->setPrepare();
        }
        else
        {
            Serial.println("frame cannot prepare");
        }
        if (isInBoundary(p))
        {
            // set next voxel
            f->set(p->x, p->y, p->z, Full, High, Full);
            // turn off last voxel
            f->set(tmp.x, tmp.y, tmp.z, Off, Off, Off);
        }
        else
        {
            // let last voxel light
            f->set(tmp.x, tmp.y, tmp.z, Full, High, Full);
        }
        if (f->isPrepare())
        {
            f->activate(getFrameCount(200));
        }
        else
        {
            memFree();
        }

        if (isInBoundary(p))
        {
            tmp.x = p->x;
            tmp.y = p->y;
            tmp.z = p->z;
        }

        // the last step mustn't change the position
        if (i == steps - 1)
        {
            *p += *v;
        }
        wait();
    }

    // reset p if last change let it move out of bounds
    if (!isInBoundary(p))
    {
        p->x = tmp.x;
        p->y = tmp.y;
        p->z = tmp.z;
    }
}

void SnakeAnimation::changeDirAndMoveForward(Point3D *p, Vector3D *v, const int steps)
{
}

void SnakeAnimation::makeLoop(Point3D *p)
{
}

Direction SnakeAnimation::randomDirection()
{
    uint8_t value = Direction::Zero;
    for (int i = 0; i < random(100) % 3; i++)
    {
        switch (random(100) % 7)
        {
        case 1:
            value |= Right;
            break;
        case 2:
            value |= Left;
            break;
        case 3:
            value |= Up;
            break;
        case 4:
            value |= Down;
            break;
        case 5:
            value |= Front;
            break;
        case 6:
            value |= Back;
            break;
        default:
            value |= Zero;
            break;
        }
    }
    return (Direction)value;
}

bool SnakeAnimation::isPossibleDirection(const Point3D *p, const Vector3D *vec)
{
    return false;
}

bool SnakeAnimation::isInBoundary(const Point3D *p)
{
    if (p->x < 0 || p->x > 8)
        return false;
    if (p->y < 0 || p->y > 8)
        return false;
    if (p->z < 0 || p->z > 8)
        return false;
    return true;
}
