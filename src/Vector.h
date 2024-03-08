#include <Arduino.h>
#ifndef Vector_h
#define Vector_h

#include "MathUtil.h"

/// @brief Vector is used to calculate the positions and movements of voxels in the cube (three dimensional space).
class Vector3D
{
public:
  float x, y, z;

  Vector3D();
  Vector3D(float x, float y, float z);
  Vector3D(const Vector3D &vec);

  // assignment
  Vector3D &operator=(const Vector3D &a);

  // movements
  Vector3D operator+(const Vector3D &a) const;
  Vector3D operator-(const Vector3D &a) const;
  void operator+=(const Vector3D &a);
  void operator-=(const Vector3D &a);

  Vector3D operator*(const int a) const;
  Vector3D operator/(const int a) const;
  void operator*=(const int a);
  void operator/=(const int a);
  Vector3D operator*(const float a) const;
  Vector3D operator/(const float a) const;
  void operator*=(const float a);
  void operator/=(const float a);

  // comparison
  bool operator==(const Vector3D &a) const;
  bool operator!=(const Vector3D &a) const;

  /// @brief Set direction coordinates to get the unit vector of the direction. Can be used to set a direction by using the Direction enum (e.g. Left|Up, Right, Down|Back, Right|Up|Front).
  /// @param direction
  static Vector3D getStandardBaseVector(const Direction direction);

  /// @brief Set the direction coordinates to get the unit vector for this direction. Could be used to get a random direction.
  /// @param direction unless there are 6 base directions the max value is maximum value of 6 bits (63)
  static Vector3D getStandardBaseVector(const uint8_t direction);

  /// @brief Set direction coordinates to get the unit vector of the direction. Can be used to set a direction by using the Direction enum (e.g. Left|Up, Right, Down|Back, Right|Up|Front).
  /// @param direction
  static Vector3D getUnitVector(const Direction direction);

  /// @brief Set the direction coordinates to get the unit vector for this direction. Could be used to get a random direction.
  /// @param direction unless there are 6 base directions the max value is maximum value of 6 bits (63)
  static Vector3D getUnitVector(const uint8_t direction);

  /// @brief Building the magnitude of a vector.
  /// @param vector
  /// @return
  float magnitude() const;

  /// @brief Sets the direction of the vector to its opposite.
  /// @param vector the vector to change
  Vector3D inverse() const;

  /// @brief Normalize this vector.
  void normalize();

  /// @brief Get the normalized vector of this vector.
  /// @return the normalized vector
  Vector3D normalized() const;

  /// @brief Build the cross product of two vectors. The cross product is used to evaluate a perpendicular vector.
  /// @param cross the resulting cross product
  /// @param vec
  Vector3D crossProduct(const Vector3D &vec) const;

  /// @brief Determines the dot product of vector a and vector b. The dot product is 0 when the vectors are perpendicular to each other.
  /// @param vec
  /// @return
  float dotProduct(const Vector3D &vec) const;

  /// @brief round the coordinates up to int positions
  void rnd();

  /// @brief Print current state to Serial 
  void print() const;

  /// @brief Indicats whether the given vector is the zero vector (0,0,0).
  /// @param vector
  /// @return
  bool isZeroVector() const;

  /// @brief Indicates whether the given vector is a unit vector
  /// @param vector
  /// @return
  bool isUnitVector() const;

  bool isStandardBaseVector() const;
};
#endif