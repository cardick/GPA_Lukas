#include "AnimationOrchestration.h"

#include "MemoryFree.h"
#include "LightCube.h"
#include "Coloring.h"
#include "Color.h"

#include "Animation.h"
#include "ColorSpectrum.h"
#include "Eraser.h"
#include "SnakeAnimation.h"
#include "GpaAnimation.h"
#include "SinusAnimation.h"

AnimationOrchestration::AnimationOrchestration() : eraser(new Eraser()), eraseColors(new SolidColoring()), animation(nullptr), finished(true)
{
    ((SolidColoring *)eraseColors)->setColor(Color(Medium, Low, High));
}

AnimationOrchestration::~AnimationOrchestration()
{
    delete eraser;
    delete eraseColors;
    delete animation;
}

void AnimationOrchestration::run()
{

    finished = false;
    intro();

    // while (LightCube::getInstance().isBusy() && freeMemory() < 140)
    // { /*wait for space*/
    // }

    // tunnel();
    // if (animation != nullptr)
    // {
    //     animation->run();
    // }
    // while (LightCube::getInstance().isBusy() && freeMemory() < 140)
    // { /*wait for space*/
    // }
    // animation = nullptr;

    // sin1();

    // ((SolidColoring *)eraseColors)->setColor(Color(Low, Full, Medium));
    // if(eraser!=nullptr) {
    //     ((Eraser *)eraser)->run(Eraser::BTF, eraseColors, false, 90);
    // } else {
    //     Serial.println(F("eraser has been deleted."));
    // }
    // // Serial.println(freeMemory());
    // // outro();

    finished = true;
}

bool AnimationOrchestration::isFinished()
{
    return finished;
}
// void AnimationOrchestration::snake()
// {
//     animation = new SnakeAnimation();
// }

void AnimationOrchestration::colors()
{
    animation = new ColorSpectrum();
}

void AnimationOrchestration::tunnel()
{
    animation = new GpaAnimation();
}

void AnimationOrchestration::sinus()
{
    animation = new SinusAnimation();
    // ((SinusAnimation*)animation)->run(0, 10000);
    // ((SinusAnimation*)animation)->run(1, 5000);
}

void AnimationOrchestration::intro()
{
    colors();
    if (animation != nullptr)
    {
        animation->run();
    }
    
    while (LightCube::getInstance().isBusy())// && freeMemory() < 140)
    { /*wait for space*/
    }
    delete animation;
    animation = nullptr;

    ((Eraser *)eraser)->run(Eraser::DTU, eraseColors, false, 90);
}

void AnimationOrchestration::outro()
{
    tunnel();

    while (LightCube::getInstance().isBusy() && freeMemory() < 140)
    { /*wait for space*/
    }

    if (animation != nullptr)
    {
        ColorSpace cs = ColorSpace(8, 8, 8);
        ((GpaAnimation *)animation)->run(2000, &cs);
    }
    animation = nullptr;
    while (LightCube::getInstance().isBusy() && freeMemory() < 140)
    { /*wait for space*/
    }
}

void AnimationOrchestration::sin1()
{
    while (LightCube::getInstance().isBusy() && freeMemory() < 140)
    { /*wait for space*/
    }

    sinus();
    if (animation != nullptr)
    {
        ((SinusAnimation *)animation)->run(0, 3000);
    }
    animation = nullptr;
}

void AnimationOrchestration::sin2()
{
    sinus();
    if (animation != nullptr)
    {
        ((SinusAnimation *)animation)->run(1, 4000);
    }

    while (LightCube::getInstance().isBusy() && freeMemory() < 140)
    { /*wait for space*/
    }
    animation = nullptr;

    ((SolidColoring *)eraseColors)->setColor(Color(Full, High, High));
    ((Eraser *)eraser)->run(Eraser::LTR, eraseColors, false, 90);
    Serial.println(freeMemory());
}