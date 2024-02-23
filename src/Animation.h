#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef Animation_h
#define Animation_h

#include "LightCube.h"

/// @brief An animation that runs on the LED cube.
class Animation {

    public:
        /// @brief Run the animation.
        virtual void run() = 0;
    protected:
        /// @brief Wait until light cube can further process.
        void wait() {
            while(LightCube::getInstance().isBusy()) 
            { 
                // do nothing, just wait
            }
        };
};

#endif
