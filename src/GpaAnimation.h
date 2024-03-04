#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef GpaAnimation_h
#define GpaAnimation_h

#include "Animation.h"
#include "Vector.h"

class GpaAnimation : public Animation {
    public:
        void run();
        void run(unsigned long millis);
    private:
        void moveTunnel(Frame *frame);
        void moveTunnelBack(Frame *frame);
        unsigned long currentMillis();

};

#endif