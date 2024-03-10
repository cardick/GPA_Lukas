#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef GpaAnimation_h
#define GpaAnimation_h

#include "Animation.h"
#include "Vector.h"
#include "Coloring.h"

class GpaAnimation : public Animation {
    public:
        void run();
        void run(unsigned long millis, Coloring* coloring);
    private:
        void moveTunnel(Frame *frame, Coloring* coloring);
        void moveTunnelBack(Frame *frame, Coloring* coloring);
        unsigned long currentMillis();

};

#endif