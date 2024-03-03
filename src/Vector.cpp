#include <Arduino.h>
#include "Vector.h"

void Vector::setDirection(Vector3D *vector, const Direction direction)
{
    setDirection(vector, (uint8_t)direction);
}

void Vector::setDirection(Vector3D *vector, const uint8_t direction)
{
    // zero vector - no direction
    vector->vx = 0;
    vector->vy = 0;
    vector->vz = 0;

    if(direction>63) {
        return;
    }

    // set directions to vector
    for (uint8_t i = 0; i < 6; i++)
    {
        switch (direction & (1 << i))
        {
        case Front:
            vector->vx += 1;
            break;
        case Left:
            vector->vy += 1;
            break;
        case Up:
            vector->vz += 1;
            break;
        case Back:
            vector->vx -= 1;
            break;
        case Right:
            vector->vy -= 1;
            break;
        case Down:
            vector->vz -= 1;
            break;
        }
    }
}

void Vector::add(Vector3D *vectorA, const Vector3D *vectorB)
{
    vectorA->vx += vectorB->vx;
    vectorA->vy += vectorB->vy;
    vectorA->vz += vectorB->vz;
}

void Vector::add(Vector3D *product, const Vector3D *vectorA, const Vector3D *vectorB)
{
    product->vx = vectorA->vx + vectorB->vx;
    product->vy = vectorA->vy + vectorB->vy;
    product->vz = vectorA->vz + vectorB->vz;
}

void Vector::add(Vector3D *vector, int scalar)
{
    vector->vx += scalar;
    vector->vy += scalar;
    vector->vz += scalar;
}

void Vector::multiply(Vector3D *vector, int scalar)
{
    vector->vx *= scalar;
    vector->vy *= scalar;
    vector->vz *= scalar;
}

double Vector::magnitude(const Vector3D *vector)
{
    return sqrt(sq(vector->vx) + sq(vector->vy) + sq(vector->vz));
}

void Vector::inverse(Vector3D *vector)
{
    vector->vx = vector->vx * (-1);
    vector->vy = vector->vy * (-1);
    vector->vz = vector->vz * (-1);
}

void Vector::crossProduct(Vector3D *cross, const Vector3D *vectorA, const Vector3D *vectorB)
{
    cross->vx = (vectorA->vy * vectorB->vz) - (vectorA->vz * vectorB->vy);
    cross->vy = (vectorA->vz * vectorB->vx) - (vectorA->vx * vectorB->vz);
    cross->vz = (vectorA->vx * vectorB->vy) - (vectorA->vy * vectorB->vx);
}

int Vector::getDotProduct(const Vector3D *vectorA, const Vector3D *vectorB)
{
    return (vectorA->vx * vectorB->vx) + (vectorA->vy * vectorB->vy) + (vectorA->vz * vectorB->vz);
}

bool Vector::isZeroVector(const Vector3D *vec)
{
    return vec->vx == 0 && vec->vy == 0 && vec->vz == 0;
}

bool Vector::isDirectionVector(const Vector3D *vector)
{
    return (vector->vx <= 1 || vector->vx >= -1) && (vector->vy <= 1 || vector->vy >= -1) && (vector->vz <= 1 || vector->vz >= -1);
}

bool Vector::equals(const Vector3D *vectorA, const Vector3D *vectorB)
{
    return (vectorA->vx == vectorB->vx) && (vectorA->vy == vectorB->vy) && (vectorA->vz == vectorB->vz);
}