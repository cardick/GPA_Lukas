#include <Arduino.h>
#ifndef Quaternion_h
#define Quaternion_h

#include "Vector.h"

/// @brief Quaternion is an extension of complex numbers to the three 
/// dimensional space. The main practical use of it is in how they describe 
/// 3d rotation.
///
/// q * some 3D point * q pow -1
class Quaternion
{
public:
    float w; // 
    Vector3D unitVector;

    /// @brief 
    /// @param a 
    /// @param unitVector defines the axis of rotation
    Quaternion(float a, const Vector3D &unitVector);
    Quaternion();
    Quaternion(const Quaternion &q);
    // copy assignment
    Quaternion &operator=(const Quaternion &q);
    void convertAxisAngle();

    // moving (add subtract)
    Quaternion operator+(const Quaternion &q) const;
    Quaternion operator-(const Quaternion &q) const;
    void operator+=(const Quaternion &q);
    void operator-=(const Quaternion &q);

    // scaling (multiply divide by scalar)
    Quaternion operator*(float s) const;
    Quaternion operator/(float s) const;

    void operator*=(float s);
    void operator/=(float s);

    // multiply quaternions
    Quaternion operator*(const Quaternion &q) const;
    Quaternion operator/(const Quaternion &q) const;
    void operator*=(const Quaternion &q);

    // dot product
    float dot(const Quaternion &q) const;
    float operator%(const Quaternion &q) const;

    // inverse
    void inverse();
    Quaternion inversed() const;
    // get conjugate (negative imaginary part)
    void conjugate();
    Quaternion conjugated() const;
    // unit quaternion
    void normalize();
    Quaternion normalized() const;
    // magnitude or length of the quaterion
    float magnitude() const;
    float norm() const;
    // rotate v by quaternion
    void rotate(Vector3D &v) const;
    Vector3D rotated(const Vector3D &v) const;
};

#endif