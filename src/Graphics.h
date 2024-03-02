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

        static void drawColumn(const int column, const Color color);
        
        static void drawLayer(const int layer, const Color color);

        static void drawColumn(const int column, const Color color, const long millis);

        static void drawLine(Point3D point, Vector3D direction, Coloring& coloring);

        static void drawLine(Point3D point, Vector3D direction, Coloring& coloring, long millis);

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
        /// @param point starting point
        /// @param a direction for line a
        /// @param b direction for line b
        /// @param lenghtA length of line a
        /// @param lenghtB length of line b
        /// @param coloring the coloring setting for the rectangle 
        static void drawRectangle(const Point3D * point, Direction a, Direction b, const int lengthA, const int lengthB, Coloring& coloring, Frame *frame);

        /// @brief Draws a filled rectangle anywhere in the cube
        /// @param point starting point
        /// @param a direction for line a
        /// @param b direction for line b
        /// @param lenghtA length of line a
        /// @param lenghtB length of line b
        /// @param color the coloring setting for the rectangle
        static void fillRectangle(Point3D point, Direction a, Direction b, int lengthA, int lenghtB, Coloring* coloring);

        /// @brief Clear all settings in cube
        static void erase();

        // move the plane via y axxis

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

        /// @brief Convert ot radians
        /// @param angle the angle in degree
        /// @return rad value
        static float toRadians(float angle) {
            return (M_PI / 180) * angle;
        }

        /// @brief Convert to degree
        /// @param radian the radian value 
        /// @return deg value
        static float toDegrees(float radian) {
            return (radian * 180) / M_PI;
        }
            
};

#endif