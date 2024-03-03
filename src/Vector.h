#include <Arduino.h>
#ifndef Vector_h
#define Vector_h

/// @brief Direction flags for the base directions.
enum Direction
{
  Zero = 0 << 0,
  Front = 1 << 0,
  Left = 1 << 1,
  Up = 1 << 2,
  Back = 1 << 3,
  Right = 1 << 4,
  Down = 1 << 5
};

/// @brief vector in a cubes or cuboid space.
struct Vector3D
{
public:
  int vx, vy, vz;

  Vector3D() : vx(0), vy(0), vz(0) {}

  Vector3D(int x, int y, int z) : vx(x), vy(y), vz(z) {}

  Vector3D operator+(const Vector3D a) const
  {
    return Vector3D(vx + a.vx, vy + a.vy, vz + a.vz);
  }

  Vector3D operator-(const Vector3D a) const
  {
    return Vector3D(vx - a.vx, vy - a.vy, vz - a.vz);
  }

  Vector3D &operator-=(const Vector3D &a)
  {
    vx -= a.vx;
    vy -= a.vy;
    vz -= a.vz;
    return *this;
  }

  Vector3D operator*(const int a) const
  {
    return Vector3D(vx * a, vy * a, vz * a);
  }

  // void toSerial() const
  // {
  //   Serial.print("[Vector3D] {x: ");
  //   Serial.print(vx);
  //   Serial.print(", y: ");
  //   Serial.print(vy);
  //   Serial.print(", z: ");
  //   Serial.print(vz);
  //   Serial.println("}");
  // }
};

/// @brief point in a cube or cuboid space.
struct Point3D
{
public:
  uint8_t x, y, z;

  Point3D() : x(0), y(0), z(0) {}

  Point3D(uint8_t x, uint8_t y, uint8_t z) : x(x), y(y), z(z) {}

  // void toSerial() const
  // {
  //   Serial.print("[Point3D] {x: ");
  //   Serial.print(x);
  //   Serial.print(", y: ");
  //   Serial.print(y);
  //   Serial.print(", z: ");
  //   Serial.print(z);
  //   Serial.println("}");
  // }

  bool operator==(const Point3D a) const
  {
    return (this->x == a.x) && (this->y == a.y) && (this->z == a.z);
  }

  bool operator!=(const Point3D a) const
  {
    return (this->x != a.x) || (this->y != a.y) || (this->z != a.z);
  }

  Point3D operator+(const Vector3D a) const
  {
    return Point3D(x + a.vx, y + a.vy, z + a.vz);
  }

  Point3D &operator+=(const Vector3D &a)
  {
    x += a.vx;
    y += a.vy;
    z += a.vz;
    return *this;
  }

  Point3D operator*(const Vector3D a) const
  {
    return Point3D(x * a.vx, y * a.vy, z * a.vz);
  }

  Point3D operator*(const int a) const
  {
    return Point3D(x * a, y * a, z * a);
  }
};

/// @brief Vector class defines statis methods to work with vectors.
class Vector
{
public:
  /// @brief Set direction coordinates to get the unit vector of the direction. Can be used to set a direction by using the Direction enum (e.g. Left|Up, Right, Down|Back, Right|Up|Front).
  /// @param vector
  /// @param direction
  static void setDirection(Vector3D *vector, const Direction direction);

  /// @brief Set the direction coordinates to get the unit vector of the direction. Could be used to get a random direction.
  /// @param vector the vector to set the coordinates
  /// @param direction unless there are 6 base directions the max value is maximum value of 6 bits (63)
  static void setDirection(Vector3D *vector, const uint8_t direction);

  /// @brief Add vector a to vector b, where vector a holds the product of both.
  /// @param vectorA
  /// @param vectorB
  static void add(Vector3D *vectorA, const Vector3D *vectorB);

  /// @brief Add vector a to vector b and stores the result in the product vector.
  /// @param product
  /// @param vectorA
  /// @param vectorB
  static void add(Vector3D *product, const Vector3D *vectorA, const Vector3D *vectorB);

  /// @brief Scalar addition to a vector
  /// @param vector
  /// @param scalar
  static void add(Vector3D *vector, int scalar);

  /// @brief Scalar multiplication to a vector.
  /// @param vector
  /// @param scalar
  static void multiply(Vector3D *vector, int scalar);

  /// @brief Building the magnitude of a vector.
  /// @param vector
  /// @return
  static double magnitude(const Vector3D *vector);

  /// @brief Sets the direction of the vector to its opposite.
  /// @param vector the vector to change
  static void inverse(Vector3D *vector);

  /// @brief Build the cross product of two vectors. The cross product is used to evaluate a perpendicular vector.
  /// @param cross the resulting cross product
  /// @param vectorA
  /// @param vectorB
  static void crossProduct(Vector3D *cross, const Vector3D *vectorA, const Vector3D *vectorB);

  /// @brief Determines the dot product of vector a and vector b. The dot product is 0 when the vectors are perpendicular to each other.
  /// @param vectorA
  /// @param vectorB
  /// @return
  static int getDotProduct(const Vector3D *vectorA, const Vector3D *vectorB);

  /// @brief Indicats whether the given vector is the zero vector (0,0,0).
  /// @param vector
  /// @return
  static bool isZeroVector(const Vector3D *vector);

  /// @brief Indicates whether the given vector is a direction vector
  /// @param vector
  /// @return
  static bool isDirectionVector(const Vector3D *vector);

  /// @brief Checks whether vector a is equal to vector b
  /// @param vectorA
  /// @param vectorB
  /// @return
  static bool equals(const Vector3D *vectorA, const Vector3D *vectorB);

  static void printVector(const Vector3D * vec);

  static void printPoint(const Point3D * point);
};

#endif