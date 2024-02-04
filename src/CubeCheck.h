#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef CubeCheck_h
#define CubeCheck_h

#include "Frame.h"

class CubeCheck {
    public:
        static void testCubeFunctionality();

    private:
        static bool waitTillEnd();
        static bool wait();
};

#endif