#include <Arduino.h>
#include "SnakeAnimation.h"
#include "Coloring.h"
#include "Vector.h"

void SnakeAnimation::run()
{
    // LightCube::getInstance().getFrame()->setAllOff();
    // LightCube::getInstance().getFrame()->activate(1);
    wait();

    Snake snake = Snake(1);
    snake.set(4,3,6);//static_cast<uint8_t>(random(100)) % 8, static_cast<uint8_t>(random(100)) % 8, static_cast<uint8_t>(random(100)) % 8);

    Vector3D vec = Vector3D();

    for (int i = 0; i < 50; i++)
    {
        uint8_t rndDir = randomDirection();
        while (rndDir == 0)
        {
            rndDir = randomDirection();
        }

        vec = Vector3D::getUnitVector(rndDir);

        // @todo: get new directory as long as random direction is not possible

        // @todo: get random action for the snake
        switch (0)
        {
        case 0:
            moveForward(snake, vec, max(3, random(100) % 8));
            break;
        case 1:
            changeDirAndMoveForward(snake, vec, 0);
            break;
        default:
            makeLoop(snake);
            break;
        }
    }
    Serial.println("snake finished.");
}

void SnakeAnimation::moveForward(Snake &snake, const Vector3D &v, const int steps)
{
    Serial.println("move");
    Frame *f = LightCube::getInstance().getFrame();
    if(f->canPrepare()) {
        f->setPrepare();
        f->setAllOff();
    } else {
        Serial.println(F("Couldn't prepare frame."));
    }

    // draw initial snake
    for (int i = 0; i < snake.getLength(); i++)
    {
        if(isInBoundary(snake.get(i))) 
        {
            f->set(snake.get(i).x, snake.get(i).y, snake.get(i).z, Full, Medium, Low);
        }
        else {
            snake.get(i).print();
            Serial.println(F("snake not in boundaries."));
        }
    }
    
    for (int i = 0; i < steps; i++)
    {
        if (f->canPrepare() && !f->isPrepare())
        {
            f->setPrepare();
        } else {
            Serial.println(f->getState());
        }

        if (isInBoundary(snake.get()))
        {
            // set next voxel
            f->set(snake.get().x, snake.get().y, snake.get().z, Full, High, Full);

            // turn off the snakes ex last tail element
            if (isInBoundary(snake.toDrop()))
            {
                f->set(snake.toDrop().x, snake.toDrop().y, snake.toDrop().z, Off, Off, Off);
            }
        }

        if (f->isPrepare())
        {
            f->activate(getFrameCount(100));
        }
        else
        {
            Serial.println(F("couldn't activate frame."));
            memFree();
        }

        // the last step mustn't change the position
        if (i <= (steps - 1))
        {
            // snake.get().print();
            // v.print();

            Voxel next = snake.get() + v;
            
            if (isInBoundary(next))
            {
                snake.set(next);
            }else{
                Serial.println(F("cannot move that direction"));
            }
        }
        wait();
    }
}

void SnakeAnimation::changeDirAndMoveForward(Snake &snake, Vector3D &v, const int steps)
{
}

void SnakeAnimation::makeLoop(Snake &snake)
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

bool SnakeAnimation::isPossibleDirection(const Voxel &vox, const Vector3D &vec)
{
    return false;
}

bool SnakeAnimation::isInBoundary(const Voxel &vox)
{
    if (vox.x < 0 || vox.x >= 8)
        return false;
    if (vox.y < 0 || vox.y >= 8)
        return false;
    if (vox.z < 0 || vox.z >= 8)
        return false;
    return true;
}