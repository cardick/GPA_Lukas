#include "Voxel.h"

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
    return Voxel(static_cast<uint8_t>(round(x + a.x)), static_cast<uint8_t>(round(y + a.y)), static_cast<uint8_t>(round(z + a.z)));
}

Voxel Voxel::operator-(const Vector3D &a) const
{
    return Voxel(static_cast<uint8_t>(round(x - a.x)), static_cast<uint8_t>(round(y - a.y)), static_cast<uint8_t>(round(z - a.z)));
}

void Voxel::operator+=(const Vector3D &a)
{
    x += static_cast<uint8_t>(round(a.x));
    y += static_cast<uint8_t>(round(a.y));
    z += static_cast<uint8_t>(round(a.z));
}

void Voxel::operator-=(const Vector3D &a)
{
    x -= static_cast<uint8_t>(round(a.x));
    y -= static_cast<uint8_t>(round(a.y));
    z -= static_cast<uint8_t>(round(a.z));
}

Voxel Voxel::operator*(const Vector3D &a) const
{
    return Voxel(static_cast<uint8_t>(round(x * a.x)), static_cast<uint8_t>(round(y * a.y)), static_cast<uint8_t>(round(z * a.z)));
}

Voxel Voxel::operator*(const int a) const
{
    return Voxel(x * a, y * a, z * a);
}

void Voxel::operator*=(const Vector3D &a)
{
    x = static_cast<uint8_t>(round(x * a.x));
    y = static_cast<uint8_t>(round(y * a.y));
    z = static_cast<uint8_t>(round(z * a.z));
}
void Voxel::operator*=(const int a)
{
    x = static_cast<uint8_t>(round(x * a));
    y = static_cast<uint8_t>(round(y * a));
    z = static_cast<uint8_t>(round(z * a));
}