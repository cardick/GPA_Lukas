#include <Arduino.h>
#include "Vector.h"


// Vector3D class implementation

Vector3D::Vector3D() : x(0), y(0), z(0) {}
Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}
Vector3D::Vector3D(const Vector3D &vec) : x(vec.x), y(vec.y), z(vec.z) {}

Vector3D &Vector3D::operator=(const Vector3D &a)
{
    x = a.x;
    y = a.y;
    z = a.z;
    return *this;
}

Vector3D Vector3D::operator+(const Vector3D &a) const
{
    return Vector3D(x + a.x, y + a.y, z + a.z);
}

Vector3D Vector3D::operator-(const Vector3D &a) const
{
    return Vector3D(x - a.x, y - a.y, z - a.z);
}

void Vector3D::operator+=(const Vector3D &a)
{
    x += a.x;
    y += a.y;
    z += a.z;
}

void Vector3D::operator-=(const Vector3D &a)
{
    x -= a.x;
    y -= a.y;
    z -= a.z;
}

Vector3D Vector3D::operator*(const int a) const
{
    return Vector3D(x * a, y * a, z * a);
}

Vector3D Vector3D::operator/(const int a) const
{
    return Vector3D(x / a, y / a, z / a);
}

void Vector3D::operator*=(const int a)
{
    x *= a;
    y *= a;
    z *= a;
}

void Vector3D::operator/=(const int a)
{
    x = x / a;
    y = y / a;
    z = z / a;
}

Vector3D Vector3D::operator*(const float a) const
{
    return Vector3D(x * a, y * a, z * a);
}

Vector3D Vector3D::operator/(const float a) const
{
    return Vector3D(x / a, y / a, z / a);
}

void Vector3D::operator*=(const float a)
{
    x *= a;
    y *= a;
    z *= a;
}

void Vector3D::operator/=(const float a)
{
    x = x / a;
    y = y / a;
    z = z / a;
}

bool Vector3D::operator==(const Vector3D &a) const
{
    return (x == a.x) && (y == a.y) && (z == a.z);
}

bool Vector3D::operator!=(const Vector3D &a) const
{
    return (x != a.x) || (y != a.y) || (z != a.z);
}

float Vector3D::magnitude() const
{
    return sqrt(sq(x) + sq(y) + sq(z));
}

Vector3D Vector3D::inverse() const
{
    return *this * (-1);
}

void Vector3D::normalize()
{
    *this *= (1 / magnitude());
}

Vector3D Vector3D::normalized() const
{
    return (*this) * (1 / magnitude());
}

Vector3D Vector3D::crossProduct(const Vector3D &vec) const
{
    return Vector3D(
        ((y * vec.z) - (z * vec.y)),
        ((z * vec.x) - (x * vec.z)),
        ((x * vec.y) - (y * vec.x)));
}

float Vector3D::dotProduct(const Vector3D &vec) const
{
    return (x * vec.x) + (y * vec.y) + (z * vec.z);
}

void Vector3D::rnd()
{
    this->x = round(this->x);
    this->y = round(this->y);
    this->z = round(this->z);
    // Serial.print(F("rnd "));
    // Serial.print(x);
    // Serial.print(F(", "));
    // Serial.print(y);
    // Serial.print(F(", "));
    // Serial.print(z);
}

bool Vector3D::isZeroVector() const
{
    return x == 0 && y == 0 && z == 0;
}

bool Vector3D::isUnitVector() const
{
    return magnitude() == 1;
}

bool Vector3D::isStandardBaseVector() const
{
    return (x == 1 || x == 0 || x == -1) && (y == 1 || y == 0 || y == -1) && (z == 1 || z == 0 || z == -1);
}

Vector3D Vector3D::getStandardBaseVector(const Direction direction)
{
    return getStandardBaseVector((uint8_t)direction);
}

Vector3D Vector3D::getStandardBaseVector(const uint8_t direction)
{
    if (direction > 63)
    {
        return Vector3D();
    }

    // zero vector - no direction
    float x = 0;
    float y = 0;
    float z = 0;

    // set directions to vector
    for (uint8_t i = 0; i < 6; i++)
    {
        switch (direction & (1 << i))
        {
        case Front:
            x += 1;
            break;
        case Left:
            y += 1;
            break;
        case Up:
            z += 1;
            break;
        case Back:
            x -= 1;
            break;
        case Right:
            y -= 1;
            break;
        case Down:
            z -= 1;
            break;
        }
    }
    return Vector3D(x, y, z);
}

Vector3D Vector3D::getUnitVector(const Direction direction)
{
    return getUnitVector((uint8_t)direction);
}

Vector3D Vector3D::getUnitVector(const uint8_t direction)
{
    return getStandardBaseVector(direction).normalized();
}