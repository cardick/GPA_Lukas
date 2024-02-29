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
        /// @brief Run the animation
        void run();
        void run(int variant, long millis);

    private:

        void calculateSingle(Frame * frame, const Vector3D * referenceDirection, const Vector3D * poleDirection, const int poleOffset, const double amplitude, const int shift);

        /// @brief Calulate the points of the sinus plane for a frame
        /// @param frame the frame to be filled
        /// @param referenceDirection the fix direction
        /// @param poleDirection the direction of the amplitude
        /// @param poleOffset the offset to the pole axis
        /// @param amplitude an ampltude modifier
        /// @param shift the shift in the calculation to enable a movement over multiple frames
        void calculate(Frame * frame, const Vector3D * referenceDirection, const Vector3D * poleDirection, const int poleOffset, const double amplitude, const int shift);
        Color getColor(int i);
        Color getColor(bool dropping);
};

#endif