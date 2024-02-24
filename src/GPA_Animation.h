#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef GPA_Animation_h
#define GPA_Animation_h

#include "Animation.h"

class GpaAnimation : public Animation {
    public:
        void run();
    private:
};

#endif