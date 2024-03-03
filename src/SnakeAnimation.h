#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef SnakeAnimation_h
#define SnakeAnimation_h

#include "Animation.h"
#include "Vector.h"

struct Snake
{

    // BAD WORKAROUND: Since index 0 of the used array of Point3D structs makes 
    // only bullshit and I don't have a clue why, I start on index 1 and make 
    // the array bigger. However, from an outside perspective it behaves like
    // an array that starts on index 0.

public:
    /// @brief Initialize a new snake with a specified maximum length. 
    ///        Initially the snake has no no active points so all Point3D
    ///        coordinates are set to uint_8 MAX_VALUE.
    /// @param length the maximum length of the snake
    Snake(int length)
    {
        this->length = length;
        p = new Point3D[(length + 2)];
        // set last point to out of bounds for the cube
        for (int i = 0; i < length+2; i++)
        {
            p[i] = Point3D(-1, -1, -1);
        }
    }

    ~Snake()
    {
        // delete the array of points
        delete p;
        free(p);
    }

    /// @brief Get the point that steers the snake
    /// @return the Point3D object
    const Point3D *get()
    {
        return &p[1];
    }

    /// @brief Get Point3D to draw at a specific position to draw the complete 
    ///        snake. 
    /// @param index the iteration index [0 .. length] 
    /// @return a Point3D of position. This could be a Point3D with all 
    ///         coordinates set to uint_8 MAX_VALUE to indicate the position is
    ///         not set.
    const Point3D *get(int index)
    {
        if (index < 0 || index >= this->length)
        {
            return nullptr;
        }
        return &p[(index+1)];
    }

    /// @brief Sets the next position of the snake to move
    /// @param p the point the snake should move
    void set(Point3D p)
    {
        shift();
        // set first element
        this->p[1].x = p.x;
        this->p[1].y = p.y;
        this->p[1].z = p.z;
    }

    /// @brief Sets the next position of the snake to move
    /// @param x x coordinate of next position 
    /// @param y y coordinate of next position
    /// @param z z coordinate of next position
    void set(uint8_t x, uint8_t y, uint8_t z)
    {
        shift();
        this->p[1].x = x;
        this->p[1].y = y;
        this->p[1].z = z;
    }

    /// @brief Get the last element of the snakes tail
    /// @return a Point3D
    const Point3D *getLast()
    {
        return &p[length];
    }

    /// @brief Get the element to drop from the cube, when snake moves
    /// @return a Point3D to drop or a Point3D with uint_8 MAX_VALUE as 
    ///         coordinates, if there is nothing to drop
    const Point3D *getDrop()
    {
        return &p[length + 1];
    }

    /// @brief Get the length of the visible snake.
    /// @return the length
    const int getLength()
    {
        return this->length;
    }

private:
    Point3D *p;
    int length;

    /// @brief Shift all points of the snake by one. Begin at the end.
    void shift()
    {
        for (int i = length + 1; i > 1; i--)
        {
            this->p[i].x = this->p[i - 1].x;
            this->p[i].y = this->p[i - 1].y;
            this->p[i].z = this->p[i - 1].z;
        }
    }

    // TODO: Snake grow every 5 steps
    void grow(Point3D p)
    {
    }
};

class SnakeAnimation : public Animation
{
public:
    void run();

private:
    void moveForward(Snake *snake, const Vector3D *v, const int steps);
    void changeDirAndMoveForward(Snake *snake, Vector3D *v, const int steps);
    void makeLoop(Snake *snake);
    uint8_t randomDirection();
    bool isPossibleDirection(const Point3D *p, const Vector3D *v);
    bool isInBoundary(const Point3D *p);
    void printVector(const Vector3D *vec);
};

#endif