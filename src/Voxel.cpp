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