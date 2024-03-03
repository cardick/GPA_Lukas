#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef CubeCheck_h
#define CubeCheck_h

#include "Animation.h"

/// @brief Animation that checks the cube functionality
class CubeCheck : public Animation {
    public:
        void run();

    private:
        void testCubeFunctionality();
        void testBlockWise();
        void testColumns();
        void testColumnPlanes(long millis);
        void testRowPlanes(long millis);
        void testLayer(long millis);
        void testSphere();
        void moveFrontBack();
        void allOff();
};

#endif