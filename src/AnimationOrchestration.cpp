#include "AnimationOrchestration.h"

#include "Animation.h"
#include "ColorSpectrum.h"
#include "Eraser.h"
#include "SnakeAnimation.h"
#include "GpaAnimation.h"
#include "SinusAnimation.h"

void AnimationOrchestration::colorSpace()
{
    ColorSpectrum colorSpace = ColorSpectrum();
    colorSpace.run();
}

void AnimationOrchestration::eraseScreenDTU()
{
    Eraser erase = Eraser();
    erase.run(Eraser::DTU, new SolidColoring(new Color(Off, Off, Medium)), true, 110);
}

void AnimationOrchestration::tunnel()
{
    GpaAnimation animation = GpaAnimation();
    animation.run(5000, new SolidColoring(new Color(High, Full, Full)));
}

void AnimationOrchestration::sinusWave()
{
    SinusAnimation sin = SinusAnimation();
    sin.run(0, 3000);
}

void AnimationOrchestration::eraseScreenBTF()
{
    Eraser erase2 = Eraser();
    erase2.run(Eraser::LTR, new SolidColoring(new Color(Off, High, Low)), true, 110);
}

void AnimationOrchestration::coloredTunnel()
{
    GpaAnimation tunnel = GpaAnimation();
    tunnel.run(5000, new ColorSpace());
}
