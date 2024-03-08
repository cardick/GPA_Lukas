#include "Voxel.h"

Voxel::Voxel() : x(0), y(0), z(0) {}
Voxel::Voxel(fpVector3 vec) : x(round(vec.x())), y(round(vec.y())), z(round(vec.z())) {}
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

fpVector3 Voxel::operator+(const fpVector3 &v) const
{
    return fpVector3((float)x + v.x(), (float)y + v.y(), (float)z + v.z());
}

fpVector3 Voxel::operator-(const fpVector3 &v) const
{
    return fpVector3((float)x - v.x(), (float)y - v.y(), (float)z - v.z());
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
    Serial.print(F(", z="));
    Serial.print(z);
    Serial.println(F(")"));
}