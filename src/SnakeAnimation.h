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
        voxels = new Voxel[(length + 1)];
        // set last point to out of bounds for the cube
        for (int i = 0; i < length+1; i++)
        {
            voxels[i].x = DEFAULT_VALUE.x;
            voxels[i].y = DEFAULT_VALUE.y;
            voxels[i].z = DEFAULT_VALUE.z;
        }
    }

    ~Snake()
    {
        // delete the array of points
        delete [] voxels;
    }

    /// @brief Get the point that steers the snake
    /// @return the Point3D object
    const Voxel &get()
    {
        return voxels[0];
    }

    /// @brief Get Point3D to draw at a specific position to draw the complete 
    ///        snake. 
    /// @param index the iteration index [0 .. length] 
    /// @return a Point3D of position. This could be a Point3D with all 
    ///         coordinates set to uint_8 MAX_VALUE to indicate the position is
    ///         not set or the index is out of bounds.
    const Voxel& get(int index)
    {
        if (index < 0 || index >= this->length)
        {
            return DEFAULT_VALUE;
        }
        return voxels[index];
    }

    /// @brief Sets the next position of the snake to move
    /// @param p the point the snake should move
    void set(const Voxel& vox)
    {
        shift();
        // set first element
        this->voxels[0].x = vox.x;
        this->voxels[0].y = vox.y;
        this->voxels[0].z = vox.z;
    }

    /// @brief Sets the next position of the snake to move
    /// @param x x coordinate of next position 
    /// @param y y coordinate of next position
    /// @param z z coordinate of next position
    void set(uint8_t x, uint8_t y, uint8_t z)
    {
        shift();
        this->voxels[0].x = x;
        this->voxels[0].y = y;
        this->voxels[0].z = z;
    }

    /// @brief Get the last element of the snakes tail
    /// @return a Point3D
    const Voxel &getLast()
    {
        return voxels[length];
    }

    /// @brief Get the element to drop from the cube, when snake moves
    /// @return a Point3D to drop or a Point3D with uint_8 MAX_VALUE as 
    ///         coordinates, if there is nothing to drop
    const Voxel &toDrop()
    {
        return voxels[length + 1];
    }

    /// @brief Get the length of the visible snake.
    /// @return the length
    const int getLength()
    {
        return this->length;
    }

private:
    const Voxel DEFAULT_VALUE = Voxel(-1, -1, -1);

    Voxel *voxels;
    int length;

    /// @brief Shift all points of the snake by one. Begin at the end.
    void shift()
    {
        for (int i = length; i > 0; i--)
        {
            this->voxels[i].x = this->voxels[i - 1].x;
            this->voxels[i].y = this->voxels[i - 1].y;
            this->voxels[i].z = this->voxels[i - 1].z;
        }
    }

    // TODO: Snake grow every 5 steps
    void grow(Voxel p)
    {
    }
};

class SnakeAnimation : public Animation
{
public:
    void run();

private:
    void moveForward(Snake &snake, const Vector3D &vec, const int steps);
    void changeDirAndMoveForward(Snake &snake, Vector3D &vec, const int steps);
    void makeLoop(Snake &snake);
    uint8_t randomDirection();
    bool isPossibleDirection(const Voxel &vox, const Vector3D &vec);
    bool isInBoundary(const Voxel &vox);
};

#endif