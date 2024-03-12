#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef Eraser_h
#define Eraser_h

#include "Animation.h"
#include "Coloring.h"

class Eraser : public Animation
{
private:
    Coloring* offColoring;


    void eraseRightToLeft(unsigned long speed, bool onReturn, Coloring* coloring);
    void eraseBackToFront(unsigned long speed, bool onReturn, Coloring* coloring);
    void eraseDownToUp(unsigned long speed, bool onReturn, Coloring* coloring);
public:
    static const int LTR = 1;
    static const int BTF = 2;
    static const int DTU = 3;

    Eraser();
    ~Eraser();

    void run();
    void run(int type, Coloring* coloring, bool eraseOnReturn, unsigned long speed);
    void front(unsigned long speed, bool onReturn, Coloring* coloring);
    void back(unsigned long speed, bool onReturn, Coloring* coloring);
    void left(unsigned long speed, bool onReturn, Coloring* coloring);
    void right(unsigned long speed, bool onReturn, Coloring* coloring);
    void up(unsigned long speed, bool onReturn, Coloring* coloring);
    void down(unsigned long speed, bool onReturn, Coloring* coloring);

    void drawColumns(uint8_t drawColumn, uint8_t eraseColumn, Coloring *coloring);
};

#endif