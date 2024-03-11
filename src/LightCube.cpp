#include <SPI.h>
#include "LightCube.h"
#include "MemoryFree.h"

LightCube::LightCube() : frameRate(0), frame(new Frame()), initialized(false)
{
    Serial.println(F("[Cube] init"));
}

bool LightCube::isInitialized()
{
    return initialized;
}

LightCube &LightCube::getInstance()
{
    static LightCube instance;
    return instance;
}

void LightCube::init(float frameRate)
{
    if (isInitialized())
    {
        return;
    }
    this->frameRate = frameRate;
    initialized = true;
}

uint8_t LightCube::getRowSize()
{
    return isInitialized() ? this->frame->getRows() : 0;
}

uint8_t LightCube::getColSize()
{
    return isInitialized() ? this->frame->getCols() : 0;
}

uint8_t LightCube::getLayerSize()
{
    return isInitialized() ? this->frame->getLayers() : 0;
}

Frame *LightCube::getFrame()
{
    return isInitialized() ? this->frame : nullptr;
}

const float LightCube::getFrameRate()
{
    return isInitialized() ? this->frameRate : 0;
}

bool LightCube::isIdle()
{
    return isInitialized() ? this->frame->isIdle() : false;
}

bool LightCube::isBusy()
{
    return this->initialized ? !this->frame->canPrepare() : true;
}

void LightCube::reset()
{
    if (isInitialized())
    {
        this->frame->reset();
    }
}

void LightCube::turnOn(long millis)
{
    if (isInitialized())
    {
        long lifetime = round(this->getFrameRate() * millis / 1000);
        this->frame->setAllOn();
        this->frame->activate(lifetime);
    }
}

void LightCube::shiftLayerForTick(const uint8_t index, const uint8_t tick)
{
    if (isInitialized() && frame != nullptr)
    {
        frame->shiftLayerForTick(index, tick);
    }
    else
    {
        Serial.println(F("[cube] error: either unitialized or frame is nullptr"));
    }
}

void LightCube::prepareNextDutyCycle()
{
    // decrement the lifetime of current frame
    if (isInitialized())
    {
        this->frame->decrementLifeCycle();
    }
}