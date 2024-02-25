#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef Graphics_h
#define Graphics_h

#include "Vector.h"
#include "Coloring.h"

class Graphics {

    public:

        static void drawColumn(const int column, const Color color);
        
        static void drawLayer(const int layer, const Color color);

        static void drawColumn(const int column, const Color color, const long millis);

        static void drawLine(Point3D point, Vector3D direction, Coloring& coloring);

        static void drawLine(Point3D point, Vector3D direction, Coloring& coloring, long millis);

        /// @brief Draw a rectangle anywhere in the cube
        /// @param point starting point
        /// @param a direction for line a
        /// @param b direction for line b
        /// @param lenghtA length of line a
        /// @param lenghtB length of line b
        /// @param coloring the coloring setting for the rectangle 
        static void drawRectangle(Point3D point, Direction a, Direction b, int lengthA, int lenghtB, Coloring* coloring);

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
            
};

#endif