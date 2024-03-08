#include <Arduino.h>
#ifndef VectorMath_h
#define VectorMath_h

#include "MathUtil.h"
#include "fpVector3.h"
#include "Voxel.h"

///  @brief sinus theta whereas theta is of 360/28 angle (outer ring of the 8x8x8 cube related to the cubes' center)
#define SIN_THETA_CTR 0.222520885
/// @brief  cosinus theta whereas theta is of 360/28 angle (outer ring of the 8x8x8 cube related to the cubes' center)
#define COS_THETA_CTR 0.974927923
/// @brief sinus theta2, theta2 is 360/20 angle (second outer ring of the 8x8x8 cube related to the cubes' center)
#define SIN_THETA2_CTR 0.309016994
/// @brief cosinus theta2, theta2 is 360/20 angle (second outer ring of the 8x8x8 cube related to the cubes' center)
#define COS_THETA2_CTR 0.951056516
/// @brief sinus theta3, theta3 is 360/12 angle (second inner ring of the 8x8x8 cube related to the cubes' center)
#define SIN_THETA3_CTR 0.5
/// @brief cosinus theta3, theta3 is 360/12 angle (second inner ring of the 8x8x8 cube related to the cubes' center)
#define COS_THETA3_CTR 0.866025404
/// @brief sinus theta4, theta4 is 360/4 angle (inner ring of the 8x8x8 cube related to the cubes' center)
#define SIN_THETA4_CTR 1.0
/// @brief cosinus theta4, theta4 is 360/4 angle (inner ring of the 8x8x8 cube related to the cubes' center)
#define COS_THETA4_CTR 0.0

/// @brief
class VectorMath
{
private:
    static fpVector3 CENTER;
    static fpVector3 OFFSET;

public:
    /// @brief Angle axis rotation based on Rodrigues' rotation formula
    ///     Formula:
    ///     d = (k dot v) * k
    ///     r = v - d
    ///     v' = d + r * cos(angle) + k cross r * sin(angle)
    /// Explanaition: https://www.youtube.com/watch?v=OKr0YCj0BW4
    /// The rotation works with vector displacment of the voxel to the coordinate origin.
    /// @param sinTheta sin of angle
    /// @param cosTheta cos of angle
    /// @param vox the voxel to rotate
    /// @param axis unit vector for an axis of the standard basis (e1, e2, e3) of the cartesian coordinate system
    /// @return the rotated voxel
    static Voxel axisAngleRotation(Voxel vox, fpVector3 axis, int steps);

    /// @brief Angle axis rotation based on Rodrigues' rotation formula
    ///     Formula:
    ///     term1 = v * cos(theta)
    ///     term2 = k cross v * sin(theta)
    ///     term3 = k * k dot v * (1 - cos(theta))
    ///     v' = term1 + term2 + term3
    /// Explanaition: https://medium.com/@sim30217/rodrigues-rotation-formula-47489db49050
    /// The rotation works with vector displacment of the voxel to the coordinate origin.
    /// @param sinTheta sin of angle
    /// @param cosTheta cos of angle
    /// @param vox the voxel to rotate
    /// @param axis unit vector for an axis of the standard basis (e1, e2, e3) of the cartesian coordinate system
    /// @return the rotated voxel
    static Voxel axisAngleRotation2(double sinTheta, double cosTheta, Voxel vox, fpVector3 axis);

    static double distToAxis(double px, double py, double pz, fpVector3 axis);

};

#endif