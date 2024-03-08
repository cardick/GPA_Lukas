#include <Arduino.h>
#ifndef fpVector_h
#define fpVector_h

#include "MathUtil.h"

/// @brief Vector is used to calculate the positions and movements of voxels in the cube (three dimensional space).
class fpVector3
{
public:
    fpVector3();
    fpVector3(double x, double y, double z);
    fpVector3(const fpVector3 &vec);

    // assignment
    fpVector3 &operator=(const fpVector3 &a);

    // movements
    fpVector3 operator+(const fpVector3 &a) const;
    fpVector3 operator-(const fpVector3 &a) const;
    void operator+=(const fpVector3 &a);
    void operator-=(const fpVector3 &a);

    fpVector3 operator*(const int a) const;
    fpVector3 operator/(const int a) const;
    void operator*=(const int a);
    void operator/=(const int a);
    fpVector3 operator*(const double a) const;
    fpVector3 operator/(const double a) const;
    void operator*=(const double a);
    void operator/=(const double a);

    // comparison
    bool operator==(const fpVector3 &a) const;
    bool operator!=(const fpVector3 &a) const;

    double x() const;
    double y() const;
    double z() const;

    /// @brief Set direction coordinates to get the unit vector of the direction. Can be used to set a direction by using the Direction enum (e.g. Left|Up, Right, Down|Back, Right|Up|Front).
    /// @param direction
    static fpVector3 getStandardBaseVector(const Direction direction);

    /// @brief Set the direction coordinates to get the unit vector for this direction. Could be used to get a random direction.
    /// @param direction unless there are 6 base directions the max value is maximum value of 6 bits (63)
    static fpVector3 getStandardBaseVector(const uint8_t direction);

    /// @brief Set direction coordinates to get the unit vector of the direction. Can be used to set a direction by using the Direction enum (e.g. Left|Up, Right, Down|Back, Right|Up|Front).
    /// @param direction
    static fpVector3 getUnitVector(const Direction direction);

    /// @brief Set the direction coordinates to get the unit vector for this direction. Could be used to get a random direction.
    /// @param direction unless there are 6 base directions the max value is maximum value of 6 bits (63)
    static fpVector3 getUnitVector(const uint8_t direction);

    /// @brief Building the magnitude (length) of a vector.
    /// @param vector
    /// @return
    double magnitude() const;

    /// @brief Sets the direction of the vector to its opposite.
    /// @param vector the vector to change
    fpVector3 inverse() const;

    /// @brief Normalize this vector.
    void normalize();

    /// @brief Get the normalized vector of this vector.
    /// @return the normalized vector
    fpVector3 normalized() const;

    /// @brief Build the cross product of two vectors. The cross product is used to evaluate a perpendicular vector.
    /// @param cross the resulting cross product
    /// @param vec
    fpVector3 cross(const fpVector3 &vec) const;

    /// @brief Determines the dot product (or scalar product) of vector a and vector b. The dot product is 0 when the vectors are perpendicular to each other.
    /// @param vec
    /// @return
    double dot(const fpVector3 &vec) const;

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

private:
    fpVector3(int x, int y, int z);
    static const int PRECISION = 100;
    int _x, _y, _z;
    int mult(long a, long b) const;
    double div(int a, int b) const;
};

#endif