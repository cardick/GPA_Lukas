#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef Animation_h
#define Animation_h

#include "LightCube.h"
#include "MemoryFree.h"

/// @brief An animation that runs on the LED cube.
class Animation {

    public:
        virtual ~Animation() = default;
        
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
        /// @param lifetime the lifetime in millis
        /// @return amount of frame repeats
        uint16_t getFrameCount(long lifetime) {
            float frameRate = LightCube::getInstance().getFrameRate();
            float frameCount = frameRate * lifetime / 1000;
            return max(static_cast<uint16_t>(round(frameCount)), 1);
        }

        void memFree() {
            Serial.print(F("mem free "));
            Serial.print(freeMemory());
            Serial.println(F(" bytes"));
        }
};

#endif
