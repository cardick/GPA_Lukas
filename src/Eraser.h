#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef Eraser_h
#define Eraser_h

#include "Animation.h"

class Eraser : public Animation
{
private:
    /* data */
    void eraseRightToLeft(unsigned long speed);
    void eraseBackToFront(unsigned long speed);
    void eraseDownToUp(unsigned long speed);
public:
    static const int LTR = 1;
    static const int BTF = 2;
    static const int DTU = 3;

    void run();
    void run(int type, unsigned long speed);
};

#endif