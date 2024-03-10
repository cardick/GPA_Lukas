#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef CubeCheck_h
#define CubeCheck_h

#include "Animation.h"
#include "Coloring.h"

/// @brief Animation that checks the cube functionality
class CubeCheck : public Animation {
    public:
        void run();

    private:
        Coloring* coloring;

        void testCubeFunctionality();
        void testBlockWise();
        void testColumns();
        void testColumnPlanes(long millis);
        void testRowPlanes(long millis);
        void testLayer(long millis);
        void testColorSpace(long millis);
        void testSphere();
        void testRotation();
        void moveFrontBack();
        void rotateCross();
        void allOff();
};

#endif