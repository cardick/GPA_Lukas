#include <Arduino.h>
#ifndef Voxel_h
#define Voxel_h

#include "Color.h"
#include "MathUtil.h"
#include "Vector.h"

/// @brief A voxel represents a value on the regular grid of the cube (the three dimensional space).
class Voxel
{
public:
  uint8_t x, y, z;

  Voxel();
  Voxel(uint8_t x, uint8_t y, uint8_t z);

  // assignment
  Voxel &operator=(const Voxel &a);

  // comparison
  bool operator==(const Voxel &a) const;
  bool operator!=(const Voxel &a) const;

  // movements
  Voxel operator+(const Vector3D &a) const;
  Voxel operator-(const Vector3D &a) const;

  void operator+=(const Vector3D &a);
  void operator-=(const Vector3D &a);

  Voxel operator*(const Vector3D &a) const;
  Voxel operator*(const int a) const;
  void operator*=(const Vector3D &a);
  void operator*=(const int a);

  private:
};

#endif