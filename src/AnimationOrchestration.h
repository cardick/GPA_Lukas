#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef AnimationOrchestration_h
#define AnimationOrchestration_h

#include "Animation.h"
#include "Coloring.h"
#include "Eraser.h"

class AnimationOrchestration
{
private:
    Eraser* eraser;
    Coloring* eraseColors;
    Animation* animation;
    bool finished;

    // void snake();
    void colors();
    void tunnel();
    void sinus();

    void intro();
    void outro();
    void sin1();
    void sin2();

public:

    AnimationOrchestration();
    ~AnimationOrchestration();
    void run();
    bool isFinished();
};

#endif