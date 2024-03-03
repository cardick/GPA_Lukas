#include <Arduino.h>
#include "SnakeAnimation.h"
#include "Coloring.h"
#include "Vector.h"

void SnakeAnimation::run()
{
    LightCube::getInstance().getFrame()->setAllOff();
    LightCube::getInstance().getFrame()->activate(1);
    wait();

    Snake snake = Snake(1);
    snake.set(Point3D(random(100) % 8, random(100) % 8, random(100) % 8));

    Vector3D vec = Vector3D();

    for (int i = 0; i < 200; i++)
    {
        uint8_t rndDir = randomDirection();
        while (rndDir == 0)
        {
            rndDir = randomDirection();
        }

        Vector::setDirection(&vec, rndDir);

        // @todo: get new directory as long as random direction is not possible

        // @todo: get random action for the snake
        switch (0)
        {
        case 0:
            moveForward(&snake, &vec, max(3, random(100) % 8));
            break;
        case 1:
            changeDirAndMoveForward(snake.getFirst(), &vec, 0);
            break;
        default:
            makeLoop(snake.getFirst());
            break;
        }
    }
    Serial.println("snake finished.");
}

void SnakeAnimation::moveForward(Snake *snake, Vector3D *v, int steps)
{
    // uint8_t tmpX=snake->p.x, tmpY=snake->p.y, tmpZ=snake->p.z;

    Frame *f = LightCube::getInstance().getFrame();
    f->setPrepare();
    f->setAllOff();

    for (int i = 0; i < steps; i++)
    {
        if (f->canPrepare() && !f->isPrepare())
        {
            f->setPrepare();
        }

        if (isInBoundary(snake->getFirst()))
        {
            // set next voxel
            f->set(snake->getFirst()->x, snake->getFirst()->y, snake->getFirst()->z, Full, High, Full);

            // todo: the rest of the points must also be set

            if (snake->getLost() != nullptr)
            {
                f->set(snake->getLost()->x, snake->getLost()->y, snake->getLost()->z, Off, Off, Off);
            }
        }
        else
        {
            // let last voxel light
            // f->set(tmpX, tmpY, tmpZ, Full, High, Full);
        }

        if (f->isPrepare())
        {
            f->activate(getFrameCount(100));
        }
        else
        {
            memFree();
        }

        //    ' 'if (isInBoundary(&(snake->p)))
        //     {
        //         tmpX = (*snake).p.x;
        //         tmpY = (*snake).p.y;
        //         tmpZ = (*snake).p.z;
        //     }''

        // the last step mustn't change the position
        if (i <= (steps - 1))
        {
            Point3D newPoint = *(snake->getFirst()) + *v;
            
            if (isInBoundary(&newPoint))
            {
                snake->set(newPoint);
            }
        }
        wait();
    }

    // // reset p if last change let it move out of bounds
    // if (!isInBoundary(&(snake->p)))
    // {
    //     snake->p.x = tmpX;
    //     snake->p.y = tmpY;
    //     snake->p.z = tmpZ;
    // }
}

void SnakeAnimation::changeDirAndMoveForward(Point3D *p, Vector3D *v, const int steps)
{
}

void SnakeAnimation::makeLoop(Point3D *p)
{
}

uint8_t SnakeAnimation::randomDirection()
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
    return value;
}

bool SnakeAnimation::isPossibleDirection(const Point3D *p, const Vector3D *vec)
{
    return false;
}

bool SnakeAnimation::isInBoundary(const Point3D *p)
{
    if (p->x < 0 || p->x >= 8)
        return false;
    if (p->y < 0 || p->y >= 8)
        return false;
    if (p->z < 0 || p->z >= 8)
        return false;
    return true;
}

void SnakeAnimation::printVector(const Vector3D *vec)
{
    Serial.print("dir vec ");
    Serial.print(vec->vx);
    Serial.print(" ");
    Serial.print(vec->vy);
    Serial.print(" ");
    Serial.println(vec->vz);
}