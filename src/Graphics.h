#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef Graphics_h
#define Graphics_h

#include "Vector.h"
#include "Coloring.h"

class Graphics {

    public:

        static void drawColumn(const int column, const Color color, const long millis);

        static void drawLine(Point3D point, Vector3D direction, Coloring coloring, long millis);

            // move the plane via y axxis
            
};

#endif