#include <SPI.h>
#include "LightCube.h"
#include "MemoryFree.h"

LightCube::LightCube() : frameRate(0), initialized(false)
{
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
    return isInitialized() ? frame.getRows() : 0;
}

uint8_t LightCube::getColSize()
{
    return isInitialized() ? frame.getCols() : 0;
}

uint8_t LightCube::getLayerSize()
{
    return isInitialized() ? frame.getLayers() : 0;
}

Frame *LightCube::getFrame()
{
    return isInitialized() ? &frame : nullptr;
}

const float LightCube::getFrameRate()
{
    return isInitialized() ? frameRate : 0;
}

bool LightCube::isIdle()
{
    return isInitialized() ? frame.isIdle() : false;
}

bool LightCube::isBusy()
{
    return initialized ? !frame.canPrepare() : true;
}

void LightCube::reset()
{
    if (isInitialized())
    {
        frame.reset();
    }
}

void LightCube::turnOn(long lifetime)
{
    if (isInitialized())
    {
        frame.setAllOn();
        frame.activate(static_cast<uint16_t>(max(round(getFrameRate() * lifetime / 1000), 1)));
    }
}

void LightCube::shiftLayerForTick(const uint8_t index, const uint8_t tick)
{
    if (isInitialized())
    {
        frame.shiftLayerForTick(index, tick);
    }
}

void LightCube::prepareNextDutyCycle()
{
    // decrement the lifetime of current frame
    if (isInitialized())
    {
        frame.decrementLifeCycle();
    }
}