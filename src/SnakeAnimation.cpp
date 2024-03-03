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
    snake.set(random(100) % 8, random(100) % 8, random(100) % 8);

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
            changeDirAndMoveForward(&snake, &vec, 0);
            break;
        default:
            makeLoop(&snake);
            break;
        }
    }
    Serial.println("snake finished.");
}

void SnakeAnimation::moveForward(Snake *snake, const Vector3D *v, const int steps)
{
    Serial.println("move");
    Frame *f = LightCube::getInstance().getFrame();
    f->setPrepare();
    f->setAllOff();

    // draw initial snake
    for (int i = 0; i < snake->getLength(); i++)
    {
        if(isInBoundary(snake->get(i))) 
        {
            f->set(snake->get(i)->x, snake->get(i)->y, snake->get(i)->z, Full, High, Full);
        }
    }
    
    for (int i = 0; i < steps; i++)
    {
        if (f->canPrepare() && !f->isPrepare())
        {
            f->setPrepare();
        }

        if (isInBoundary(snake->get()))
        {
            // set next voxel
            f->set(snake->get()->x, snake->get()->y, snake->get()->z, Full, High, Full);

            // turn off the snakes ex last tail element
            if (isInBoundary(snake->getDrop()))
            {
                f->set(snake->getDrop()->x, snake->getDrop()->y, snake->getDrop()->z, Off, Off, Off);
            }
        }

        if (f->isPrepare())
        {
            f->activate(getFrameCount(100));
        }
        else
        {
            memFree();
        }

        // the last step mustn't change the position
        if (i <= (steps - 1))
        {
            Vector::printPoint(snake->get());
            Vector::printVector(v);

            Point3D newPoint = *(snake->get()) + *v;
            
            if (isInBoundary(&newPoint))
            {
                snake->set(newPoint);
            }
            Serial.println();
        }
        wait();
    }
}

void SnakeAnimation::changeDirAndMoveForward(Snake *snake, Vector3D *v, const int steps)
{
}

void SnakeAnimation::makeLoop(Snake *snake)
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