#include <Arduino.h>

#ifndef Sphere_h
#define Sphere_h

#include "Voxel.h"
#include "Coloring.h"
#include "Frame.h"

class Sphere
{
private:
    double radius, x, y, z;
    Coloring *coloring;
public:
    /// @brief Initialize a new sphere object
    /// @param initialRadius 
    /// @param centerX 
    /// @param centerY 
    /// @param centerZ 
    /// @param sphereColors 
    Sphere(double initialRadius, double centerX, double centerY, double centerZ, Coloring &sphereColors);
    ~Sphere();

    /// @brief Method to set the color for sphere
    /// @param sphereColors 
    void setColoring(Coloring &sphereColors);

    /// @brief Method to rotate the sphere around an axis passing through its center and draw surface points
    /// @param axisX 
    /// @param axisY 
    /// @param axisZ 
    /// @param angle 
    void rotateAndDraw(double axisX, double axisY, double axisZ, double angle);

    /// @brief Method to draw the surface points
    void draw();

private:
    /// @brief Method to rotate the sphere around an axis passing through its center and draw surface points
    /// @param frame 
    /// @param pointX 
    /// @param pointY 
    /// @param pointZ 
    /// @param axisX 
    /// @param axisY 
    /// @param axisZ 
    /// @param angle 
    void rotateAndDrawPointAroundCenter(Frame * frame, uint8_t pointX, uint8_t pointY, uint8_t pointZ, double axisX, double axisY, double axisZ, double angle);

    /// @brief Method to draw a surface point of the cube 
    /// @param frame 
    /// @param pointX 
    /// @param pointY 
    /// @param pointZ 
    void drawPoint(Frame * frame, uint8_t pointX, uint8_t pointY, uint8_t pointZ);

    /// @brief Method to evaluate the color value of one color from a RGB value
    /// @param index the start index of the color bits 0, 4 or 8
    /// @param value the 12 bit RGB value
    /// @return the 4 bit color value
    uint8_t colorValue(uint8_t index, uint16_t value);
};

#endif