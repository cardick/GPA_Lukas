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
    return Vector3D(round(x / a), round(y / a), round(z / a));
}

void Vector3D::operator*=(const int a)
{
    x *= a;
    y *= a;
    z *= a;
}

void Vector3D::operator/=(const int a)
{
    x = round(x / a);
    y = round(y / a);
    z = round(z / a);
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
    *this *= 1/magnitude();
}

Vector3D Vector3D::normalized() const
{
    return (*this) * 1/magnitude();
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

void Vector3D::print() const
{
    Serial.print(F("vector (x="));
    Serial.print(x);
    Serial.print(F(", y="));
    Serial.print(y);
    Serial.print(F(",z="));
    Serial.print(z);
    Serial.println(F(")"));
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


// Voxel class implementation

Voxel::Voxel() : x(0), y(0), z(0) {}
Voxel::Voxel(uint8_t x, uint8_t y, uint8_t z) : x(x), y(y), z(z) {}

Voxel &Voxel::operator=(const Voxel &a)
{
    x = a.x;
    y = a.y;
    z = a.z;
    return *this;
}

bool Voxel::operator==(const Voxel &a) const
{
    return (x == a.x) && (y == a.y) && (z == a.z);
}

bool Voxel::operator!=(const Voxel &a) const
{
    return (x != a.x) || (y != a.y) || (z != a.z);
}

Voxel Voxel::operator+(const Vector3D &a) const
{
    return Voxel(round(x + a.x), round(y + a.y), round(z + a.z));
}

Voxel Voxel::operator-(const Vector3D &a) const
{
    return Voxel(round(x - a.x), round(y - a.y), round(z - a.z));
}

void Voxel::operator+=(const Vector3D &a)
{
    x += round(a.x);
    y += round(a.y);
    z += round(a.z);
}

void Voxel::operator-=(const Vector3D &a)
{
    x -= round(a.x);
    y -= round(a.y);
    z -= round(a.z);
}

Voxel Voxel::operator*(const Vector3D &a) const
{
    return Voxel(round(x * a.x), round(y * a.y), round(z * a.z));
}

Voxel Voxel::operator*(const int a) const
{
    return Voxel(x * a, y * a, z * a);
}

void Voxel::operator*=(const Vector3D &a)
{
    x = round(x * a.x);
    y = round(y * a.y);
    z = round(z * a.z);
}
void Voxel::operator*=(const int a)
{
    x = round(x * a);
    y = round(y * a);
    z = round(z * a);
}

void Voxel::print() const
{
    Serial.print(F("voxel (x="));
    Serial.print(x);
    Serial.print(F(", y="));
    Serial.print(y);
    Serial.print(F(",z="));
    Serial.print(z);
    Serial.println(F(")"));
}

