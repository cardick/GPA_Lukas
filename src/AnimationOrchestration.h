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
public:
    static void colorSpace();
    static void eraseScreenDTU();
    static void tunnel();
    static void sinusWave();
    static void eraseScreenBTF();
    static void coloredTunnel();
};

#endif