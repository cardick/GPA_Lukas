#include "VectorMath.h"
#include "fpVector3.h"

fpVector3 VectorMath::CENTER = fpVector3(3.5, 3.5, 3.5);
fpVector3 VectorMath::OFFSET = fpVector3(0.5, 0.5, 0.5);

Voxel VectorMath::axisAngleRotation(Voxel vox, fpVector3 axis, int steps)
{
    // displacement to center of coordinate system
    fpVector3 v = (vox - CENTER);

    // k * k dot v
    fpVector3 d = axis * axis.dot(v);
    fpVector3 r = v - d;

    double sinTheta, cosTheta;

    // magnitued |r| is the shortest distance between the voxel and the axis
    double dist = r.magnitude();

    if(dist > 3) {
        // Serial.println(dist);
        sinTheta = SIN_THETA_CTR;
        cosTheta = COS_THETA_CTR;
    } else if(steps % 3 == 0 && (dist < 3 && dist >= 2)) {
        // Serial.println(dist);
        sinTheta = SIN_THETA2_CTR;
        cosTheta = COS_THETA2_CTR;
    } else if(steps % 5 == 0 && (dist < 2 && dist >= 1)) {
        // Serial.println(dist);
        sinTheta = SIN_THETA3_CTR;
        cosTheta = COS_THETA3_CTR;
    } else if( steps %7 == 0 && (dist < 1)) {
        // Serial.println(dist);
        sinTheta = SIN_THETA4_CTR;
        cosTheta = COS_THETA4_CTR;
    } else {
        // Serial.println(F("no movement"));
        return vox;
    }

    // k cross r
    fpVector3 kr = axis.cross(r);
    kr *= sinTheta;
    r *= cosTheta;

    // v' with back displacment to the cubes center
    return Voxel((d + r + kr + CENTER));
}

Voxel VectorMath::axisAngleRotation2(double sinTheta, double cosTheta, Voxel vox, fpVector3 axis)
{
    return Voxel();
}

/// @brief 
/// @param px x coordinate of the point
/// @param py y coordinate of the point
/// @param pz z coordinate of the point
/// @param axis the base vector of the axis (linear combination to standard base vector)
/// @return perpendicular ditance of P to the axis
double VectorMath::distToAxis(double px, double py, double pz, fpVector3 axis) 
{
    // axis.print();
    axis.normalize();
    // axis.print();
    fpVector3 p = fpVector3(px, py, pz);
    fpVector3 _axis = axis * 8;
    _axis -= axis;
    p = (p - _axis).cross(_axis);
    double l1 = p.magnitude();
    double l2 = _axis.magnitude();
    Serial.print(F("expected length is 7, and is "));
    Serial.println(l2);
    return l1 / l2;
}