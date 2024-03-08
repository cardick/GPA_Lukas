#include <Arduino.h>
#include "fpVector3.h"


// fpVector3 class implementation

fpVector3::fpVector3() : _x(0), _y(0), _z(0) {}
fpVector3::fpVector3(double x, double y, double z) : _x(round((x * PRECISION))), _y(round((y * PRECISION))), _z(round((z * PRECISION))) {}
fpVector3::fpVector3(int x, int y, int z) : _x(x), _y(y), _z(z) {}
fpVector3::fpVector3(const fpVector3 &vec) : _x(vec._x), _y(vec._y), _z(vec._z) {}

fpVector3 &fpVector3::operator=(const fpVector3 &a)
{
    _x = a._x;
    _y = a._y;
    _z = a._z;
    return *this;
}

fpVector3 fpVector3::operator+(const fpVector3 &a) const
{
    return fpVector3((int)(_x + a._x), (int)(_y + a._y), (int)(_z + a._z));
}

fpVector3 fpVector3::operator-(const fpVector3 &a) const
{
    return fpVector3((int)(_x - a._x), (int)(_y - a._y), (int)(_z - a._z));
}

void fpVector3::operator+=(const fpVector3 &a)
{
    _x += a._x;
    _y += a._y;
    _z += a._z;
}

void fpVector3::operator-=(const fpVector3 &a)
{
    _x -= a._x;
    _y -= a._y;
    _z -= a._z;
}

fpVector3 fpVector3::operator*(const int a) const
{
    int i = a * PRECISION;
    return fpVector3((int)mult(_x, i), (int)mult(_y, i), (int)mult(_z, i));
}

fpVector3 fpVector3::operator/(const int a) const
{
    int i = a * PRECISION;
    return fpVector3((int)div(_x, i), (int)div(_y, i), (int)div(_z, i));
}

void fpVector3::operator*=(const int a)
{
    int i = a * PRECISION;
    _x = mult(_x, i);
    _y = mult(_y, i);
    _z = mult(_z, i);
}

void fpVector3::operator/=(const int a)
{
    int i = a * PRECISION;
    _x = div(_x, i);
    _y = div(_y, i);
    _z = div(_z, i);
}

fpVector3 fpVector3::operator*(const double a) const
{
    int i = round(a * PRECISION);
    return fpVector3((int)mult(_x, i), (int)mult(_y, i), (int)mult(_z, i));
}

fpVector3 fpVector3::operator/(const double a) const
{
    int i = round(a * PRECISION);
    return fpVector3((int)div(_x, i), (int)div(_y, i), (int)div(_z, i));
}

void fpVector3::operator*=(const double a)
{
    int i = round(a * PRECISION);
    _x = mult(_x, i);
    _y = mult(_y, i);
    _z = mult(_z, i);
}

void fpVector3::operator/=(const double a)
{
    int i = round(a * PRECISION);
    _x = div(_x, i);
    _y = div(_y, i);
    _z = div(_z, i);
}

bool fpVector3::operator==(const fpVector3 &a) const
{
    return (_x == a._x) && (_y == a._y) && (_z == a._z);
}

bool fpVector3::operator!=(const fpVector3 &a) const
{
    return (_x != a._x) || (_y != a._y) || (_z != a._z);
}

double fpVector3::x() const
{
    return ((double)_x / PRECISION);
}

double fpVector3::y() const
{
    return ((double)_y / PRECISION);
}

double fpVector3::z() const
{
    return ((double)_z / PRECISION);
}

double fpVector3::magnitude() const
{
    return sqrt((double)(sq(_x/PRECISION) + sq(_y/PRECISION) + sq(_z/PRECISION)));
}

fpVector3 fpVector3::inverse() const
{
    return *this * (-1);
}

void fpVector3::normalize()
{
    *this *= (1 / magnitude());
}

fpVector3 fpVector3::normalized() const
{
    return (*this) * (1 / magnitude());
}

fpVector3 fpVector3::cross(const fpVector3 &vec) const
{
    return fpVector3(
        (int)(mult(_y, vec._z) - mult(_z, vec._y)),
        (int)(mult(_z, vec._x) - mult(_x, vec._z)),
        (int)(mult(_x, vec._y) - mult(_y, vec._x)));
}

double fpVector3::dot(const fpVector3 &vec) const
{
    return (double)(mult(_x, vec._x) + mult(_y, vec._y) + mult(_z, vec._z))/PRECISION;
}

void fpVector3::rnd()
{
    this->_x = round(this->_x);
    this->_y = round(this->_y);
    this->_z = round(this->_z);
}

bool fpVector3::isZeroVector() const
{
    return _x == 0 && _y == 0 && _z == 0;
}

bool fpVector3::isUnitVector() const
{
    return magnitude() == 1;
}

bool fpVector3::isStandardBaseVector() const
{
    return (_x == PRECISION || _x == 0 || _x == -PRECISION) && 
        (_y == PRECISION || _y == 0 || _y == -PRECISION) && 
        (_z == PRECISION || _z == 0 || _z == -PRECISION);
}

void fpVector3::print() const
{
    Serial.print(F("fpvector3 (x="));
    Serial.print(x());
    Serial.print(F(", y="));
    Serial.print(y());
    Serial.print(F(",z="));
    Serial.print(z());
    Serial.println(F(")"));
}

fpVector3 fpVector3::getStandardBaseVector(const Direction direction)
{
    return getStandardBaseVector((uint8_t)direction);
}

fpVector3 fpVector3::getStandardBaseVector(const uint8_t direction)
{
    if (direction > 63)
    {
        return fpVector3();
    }

    // zero vector - no direction
    int x = 0;
    int y = 0;
    int z = 0;

    // set directions to vector
    for (uint8_t i = 0; i < 6; i++)
    {
        switch (direction & (1 << i))
        {
        case Front:
            x += PRECISION;
            break;
        case Left:
            y += PRECISION;
            break;
        case Up:
            z += PRECISION;
            break;
        case Back:
            x -= PRECISION;
            break;
        case Right:
            y -= PRECISION;
            break;
        case Down:
            z -= PRECISION;
            break;
        }
    }
    return fpVector3((int)x, (int)y, (int)z);
}

fpVector3 fpVector3::getUnitVector(const Direction direction)
{
    return getUnitVector((uint8_t)direction);
}

fpVector3 fpVector3::getUnitVector(const uint8_t direction)
{
    return getStandardBaseVector(direction).normalized();
}

int fpVector3::mult(long a, long b) const
{
    return a * b / PRECISION;
}

double fpVector3::div(int a, int b) const
{
    double f = (double)(a * PRECISION);
    return f / (double)b;
}
