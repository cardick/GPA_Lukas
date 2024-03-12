#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef SinusAnimation_h
#define SinusAnimation_h

#include "Frame.h"
#include "Animation.h"
#include "Vector.h"
#include "Coloring.h"

class SinusAnimation : public Animation {

    public:
        SinusAnimation();
        /// @brief Run the animation
        void run();
        void run(int variant, long runtime);

    private:
        int8_t poleDirX, poleDirY, poleDirZ, refDirX, refDirY, refDirZ;

        void runSingleWave(long runtime);
        void runMultipleWaces(long runtime);

        void calculateSingleWaveFrame(const uint8_t poleOffset, const uint8_t amplitude, const uint16_t shift);

        /// @brief Calulate the points of the sinus plane for a frame
        /// @param frame the frame to be filled
        /// @param referenceDirection the fix direction
        /// @param poleDirection the direction of the amplitude
        /// @param poleOffset the offset to the pole axis
        /// @param amplitude an ampltude modifier
        /// @param shift the shift in the calculation to enable a movement over multiple frames
        void calculate(Frame * frame, const Vector3D * referenceDirection, const Vector3D * poleDirection, const int poleOffset, const double amplitude, const int shift);

        int8_t sinValue(int16_t degrees, float compress, float amplitude);
        void resetReferenceDirectionValue(uint8_t *px, uint8_t *py, uint8_t *pz);
        void resetPoleDirectionValue(uint8_t *px, uint8_t *py, uint8_t *pz);
        void incrementByPlane(uint8_t *px, uint8_t *py, uint8_t *pz);
        Color getColor(int i);
        Color getColor(bool dropping);

        void print(int8_t x,int8_t y,int8_t z) {
            Serial.print(F("(x: "));
            Serial.print(x);
            Serial.print(F(", y: "));
            Serial.print(y);
            Serial.print(F(", z: "));
            Serial.print(z);
            Serial.println(F(")"));
        }
};

#endif