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
        }

        /// @brief Get the number of frames to be displayed for the given millis
        /// @param millis the milli seconds
        /// @return amount of frame repeats
        int getFrameCount(long millis) {
            return 1;
        }
};

#endif
