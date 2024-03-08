#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef Graphics_h
#define Graphics_h

#include "Vector.h"
#include "Coloring.h"
#include "Frame.h"

class Graphics {

    public:

        static void drawColumn(const int column, Coloring& coloring);
        
        static void drawLayer(const int layer, const Color color);

        static void drawColumn(const int column, const Color color, const long millis);

        static void drawLine(Voxel voxel, Vector3D direction, Coloring& coloring);

        static void drawLine(Voxel voxel, Vector3D direction, Coloring& coloring, long millis);

        /// @brief Draw a sphere into the center of the cube
        /// @param size the diameter (in an 8x8x8 cube, a value between [1 .. 7])
        /// @param coloring the coloring for the sphere
        /// @param frame the frame to work on 
        static void drawSphere(float size, Coloring& coloring, Frame *frame);

        /// @brief Draw a sphere from the center M
        /// @param size the diameter
        /// @param mx x coordinate of M
        /// @param my y coordinate of M
        /// @param mz z coordinate of M
        /// @param coloring the coloring for the sphere
        /// @param frame the frame to work on
        static void drawSphere(float size, float mx, float my, float mz, Coloring& coloring, Frame *frame);

        /// @brief Draw a rectangle anywhere in the cube
        /// @param voxel starting voxel
        /// @param a direction for line a
        /// @param b direction for line b
        /// @param lenghtA length of line a
        /// @param lenghtB length of line b
        /// @param coloring the coloring setting for the rectangle 
        static void drawRectangle(const Voxel * voxel, Direction a, Direction b, const int lengthA, const int lengthB, Coloring& coloring, Frame *frame);

        /// @brief Draws a filled rectangle anywhere in the cube
        /// @param voxel starting voxel
        /// @param a direction for line a
        /// @param b direction for line b
        /// @param lenghtA length of line a
        /// @param lenghtB length of line b
        /// @param color the coloring setting for the rectangle
        static void fillRectangle(Voxel voxel, Direction a, Direction b, int lengthA, int lenghtB, Coloring* coloring);

        /// @brief Rotates the active frames voxels stepwise around an axis that passes through the center of the cube.
        /// @param direction the to rotate  
        /// @param degree the angle in degrees [0 .. 360]
        /// @param frameTime the time in ms for a frame
        static void rotate(Direction direction, float degree, long frameTime);

        /// @brief Clear all settings in cube
        static void erase();

        /// @brief Retrieve the color value from the RGB color representation.
        /// @param index the color index 
        /// @param value the 12-Bit RGB value
        /// @return 4-Bit color value
        static uint8_t getColorValue(uint8_t index, uint16_t value);

    private:
        /// @brief Projection of a running index onto the angle of a circle in the specified intervals.
        /// @param index the index to be projected
        /// @param iStart the start of index intervall
        /// @param iEnd the end of index intervall
        /// @param piStart the start of circle intervall
        /// @param piEnd the end of circle intervall
        /// @return the angle value in rad
        static float projToRad(float index, float iStart, float iEnd, float piStart, float piEnd) {
            float iRange = range(iStart, iEnd);
            if(iRange == 0) { return NAN; }
            float piRange = range(piStart, piEnd);
            return index * piRange / iRange;
        }

        /// @brief Get the range between a and b.
        /// @param a the start
        /// @param b the end
        /// @return the positive range value
        static float range(float a, float b) {
            return a>0 && b>0 ? (a<b ? (b-a) : (a-b)) : 
                a<0 && b<0 ? (a<b ? (b+a) : (a+b)) : 
                a<0 && b>0 ? (abs(a)+b) :
                (abs(b)+a);
        }

        static int toFrames(long millis);

        /// @brief Convert ot radians
        /// @param angle the angle in degree
        /// @return rad value
        static double toRadians(double angle) {
            return (M_PI / 180) * angle;
        }

        /// @brief Convert to degree
        /// @param radian the radian value 
        /// @return deg value
        static double toDegrees(double radian) {
            return (radian * 180) / M_PI;
        }

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
        /// @param k unit vector for an axis of the standard basis (e1, e2, e3) of the cartesian coordinate system 
        /// @return the rotated voxel
        static Voxel rodRot(double sinTheta, double cosTheta, Voxel vox, Vector3D k);

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
        /// @param k unit vector for an axis of the standard basis (e1, e2, e3) of the cartesian coordinate system 
        /// @return the rotated voxel
        static Voxel rodRot2(double sinTheta, double cosTheta, Voxel vox, Vector3D k);

        /// @brief Multiplication of floating points values as integers with a given precision.
        /// @param a a value with accuracy offset
        /// @param b b value with accuracy offset
        /// @param accuracy the precision to use
        /// @return the result with accuracy offset
        static long fpmult(long a, long b, long accuracy);
};

#endif