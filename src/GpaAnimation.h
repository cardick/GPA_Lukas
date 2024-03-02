#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef GpaAnimation_h
#define GpaAnimation_h

#include "Animation.h"

class GpaAnimation : public Animation {
    public:
        void run();
    private:
        void moveTunnel(Frame *frame);
        void moveTunnelBack(Frame *frame);
};

#endif