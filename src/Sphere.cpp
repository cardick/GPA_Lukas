#include "Sphere.h"
#include "Voxel.h"

#include "LightCube.h"
#include "Frame.h"

Sphere::Sphere(double initialRadius, double centerX, double centerY, double centerZ, Coloring &sphereColors) :
radius(initialRadius), x(centerX), y(centerY), z(centerZ), coloring(&sphereColors) {}

Sphere::~Sphere() { }

void Sphere::setColoring(Coloring &sphereColors)
{
    this->coloring = &sphereColors;
}

// void Sphere::rotate(double degree) 
// {
//   // Rotate the sphere and draw surface points
//     for (double polarAngle = 0.0; polarAngle <= M_PI; polarAngle += M_PI / 36.0) {
//         for (double azimuthalAngle = 0.0; azimuthalAngle <= 2.0 * M_PI; azimuthalAngle += M_PI / 18.0) {
//             //this->rotateAndDraw(polarAngle, azimuthalAngle);
//         }
//     }
// }

void Sphere::rotateAndDraw(double axisX, double axisY, double axisZ, double angle)
{
    // Normalize the axis vector
    double length = sqrt(axisX * axisX + axisY * axisY + axisZ * axisZ);
    axisX /= length;
    axisY /= length;
    axisZ /= length;

    // const int polarSteps = 36;
    // const int azimuthalSteps = 18;
    const int steps = 28;

    Frame *frame = LightCube::getInstance().getFrame();

    for (int i = 0; i <= steps/4; ++i) {
        // double polarAngle = static_cast<double>(i) * M_PI / static_cast<double>(polarSteps / 4);
        double polarAngle = mapToRad(1, 0, steps/4, -M_PI_4/2, M_PI_4/2);

        for (int j = 0; j <= steps/2; ++j) {
            // double azimuthalAngle = static_cast<double>(j) * 2.0 * M_PI / static_cast<double>(azimuthalSteps / 2);
            double azimuthalAngle = mapToRad(1, 0, steps/2, -M_PI_4, M_PI_4);

            // Calculate coordinates based on spherical coordinates
            double surfaceX = radius * sin(polarAngle) * cos(azimuthalAngle) + x;
            double surfaceY = radius * sin(polarAngle) * sin(azimuthalAngle) + y;
            double surfaceZ = radius * cos(polarAngle) + z;

            // Round the coordinates and add them to the set
            uint8_t roundedX = static_cast<uint8_t>(round(surfaceX));
            uint8_t roundedY = static_cast<uint8_t>(round(surfaceY));
            uint8_t roundedZ = static_cast<uint8_t>(round(surfaceZ));

            rotateAndDrawPointAroundCenter(frame, roundedX, roundedY, roundedZ, axisX, axisY, axisZ, angle);

            // Mirror the points to cover the entire surface
            if (i > 0) {
                rotateAndDrawPointAroundCenter(frame, roundedX, roundedY, static_cast<uint8_t>(2 * static_cast<int>(radius) - roundedZ), axisX, axisY, axisZ, angle);
            }
            if (j > 0) {
                rotateAndDrawPointAroundCenter(frame, roundedX, static_cast<uint8_t>(2 * static_cast<int>(radius) - roundedY), roundedZ, axisX, axisY, axisZ, angle);
                if (i > 0) {
                    rotateAndDrawPointAroundCenter(frame, roundedX, static_cast<uint8_t>(2 * static_cast<int>(radius) - roundedY), static_cast<uint8_t>(2 * static_cast<int>(radius) - roundedZ), axisX, axisY, axisZ, angle);
                }
            }
        }
    }
}

void Sphere::rotateAndDrawPointAroundCenter(Frame * frame, uint8_t pointX, uint8_t pointY, uint8_t pointZ, double axisX, double axisY, double axisZ, double angle)
{
    // Extract spherical coordinates
    double polarAngle = asin(static_cast<double>(pointY - y) / radius);
    double azimuthalAngle = atan2(static_cast<double>(pointZ - z), static_cast<double>(pointX - x));

    // Apply the rotation
    polarAngle += angle;

    // Calculate coordinates based on spherical coordinates
    double surfaceX = radius * sin(polarAngle) * cos(azimuthalAngle) + x;
    double surfaceY = radius * sin(polarAngle) * sin(azimuthalAngle) + y;
    double surfaceZ = radius * cos(polarAngle) + z;

    // Round the coordinates and add them to the new set
    uint8_t roundedX = static_cast<uint8_t>(round(surfaceX));
    uint8_t roundedY = static_cast<uint8_t>(round(surfaceY));
    uint8_t roundedZ = static_cast<uint8_t>(round(surfaceZ));

    // Get current color of voxel 
    int index = frame->getIndex(pointX, pointY, pointZ);
    uint16_t rgbVal = frame->get(index);

    // Draw voxel at new position
    frame->set(roundedX, roundedY, roundedZ, colorValue(rgbVal, 0), colorValue(rgbVal, 4), colorValue(rgbVal, 8));
}

void Sphere::draw()
{
    // const int polarSteps = 36;
    // const int azimuthalSteps = 18;
    const int steps = 28;

    Frame *frame = LightCube::getInstance().getFrame();

    for (int i = 0; i < steps; ++i) {
        // double polarAngle = static_cast<double>(i) * M_PI / static_cast<double>(polarSteps / 4);
        double polarAngle = mapToRad(1, 0, steps, -M_PI_2, M_PI_2);

        for (int j = 0; j < steps; ++j) {
            // double azimuthalAngle = static_cast<double>(j) * 2.0 * M_PI / static_cast<double>(azimuthalSteps / 2);
            double azimuthalAngle = mapToRad(1, 0, steps, -M_PI, M_PI);

            // Calculate coordinates based on spherical coordinates
            double surfaceX = radius * sin(polarAngle) * sin(azimuthalAngle) + x;
            double surfaceY = radius * sin(polarAngle) * cos(azimuthalAngle) + y;
            double surfaceZ = radius * cos(polarAngle) + z;

            // Round the coordinates and add them to the set
            uint8_t roundedX = static_cast<uint8_t>(round(surfaceX));
            uint8_t roundedY = static_cast<uint8_t>(round(surfaceY));
            uint8_t roundedZ = static_cast<uint8_t>(round(surfaceZ));

            drawPoint(frame, roundedX, roundedY, roundedZ);

            // // Mirror the points to cover the entire surface
            // if (i > 0) {
            //     drawPoint(frame, roundedX, roundedY, static_cast<uint8_t>(2 * static_cast<int>(radius) - roundedZ));
            // }
            // if (j > 0) {
            //     drawPoint(frame, roundedX, static_cast<uint8_t>(2 * static_cast<int>(radius) - roundedY), roundedZ);
            //     if (i > 0) {
            //         drawPoint(frame, roundedX, static_cast<uint8_t>(2 * static_cast<int>(radius) - roundedY), static_cast<uint8_t>(2 * static_cast<int>(radius) - roundedZ));
            //     }
            // }
        }
    }
}

void Sphere::drawPoint(Frame *frame, uint8_t pointX, uint8_t pointY, uint8_t pointZ)
{
    Color color = coloring->getColor(pointX, pointY, pointZ);
    frame->set(pointX, pointY, pointZ, color.red, color.green, color.blue);
}

double Sphere::mapToRad(int index, int from, int to, double piFrom, double piTo)
{
    double len = size(static_cast<double>(from), static_cast<double>(to));
    if(len == 0) { return NAN; }
    double piLen = size(piFrom, piTo);
    return static_cast<double>(index) * piLen / len;
}

double Sphere::size(double a, double b) {
    return a>0 && b>0 ? (a<b ? (b-a) : (a-b)) : 
        a<0 && b<0 ? (a<b ? (b+a) : (a+b)) : 
        a<0 && b>0 ? (abs(a)+b) :
        (abs(b)+a);
}

uint8_t Sphere::colorValue(uint8_t index, uint16_t value)
{
    uint8_t cval = 0b0000;
    bitWrite(cval, 0, bitRead(value, index++));
    bitWrite(cval, 1, bitRead(value, index++));
    bitWrite(cval, 2, bitRead(value, index++));
    bitWrite(cval, 3, bitRead(value, index));
    return cval;
}
