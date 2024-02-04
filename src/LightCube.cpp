#include <SPI.h>
#include "LightCube.h"

LightCube::LightCube()
{
}

LightCube& LightCube::getInstance()
{
    static LightCube instance;
    return instance;
}

void LightCube::init(float frameRate)
{
    this->frameRate = frameRate;
    this->frame = Frame();
}

uint8_t LightCube::getRowSize()
{
    return this->frame.getRows();
}

uint8_t LightCube::getColSize()
{
    return this->frame.getCols();
}

uint8_t LightCube::getLayerSize()
{
    return this->frame.getLayers();
}

Frame* LightCube::getFrame()
{
    return &this->frame;
}

const float LightCube::getFrameRate()
{
    return this->frameRate;
}

bool LightCube::isIdle()
{
    return this->frame.isIdle();
}

bool LightCube::isBusy()
{
    return !this->frame.canPrepare();
}

void LightCube::reset()
{
    this->frame.reset();
}

void LightCube::turnOn(long millis)
{
    long lifetime = round(this->getFrameRate() * millis/1000);
    this->frame.setAllOn();
    this->frame.activate(lifetime);
}

void LightCube::shiftLayerForTick(const int index, const int tick)
{
    this->frame.shiftLayerForTick(index, tick);
    // // calculate the shift offset to begin shifting out the layer
    // // there is maybe an offset of unused ports on the shift registers; this depends on the cubes size
    // int shift = (((getRowSize() * 3 * getColSize()) + getLayerSize()) % 8) - 1;

    // // correct modulo 8 is 0
    // shift = shift == -1 ? 7 : shift;

    // // transfer LED settings to SPI
    // transferLEDs(index, tick, &shift);
}

// /**
//  * This is doing the shift out and the spy transfer
//  * @param index from 0 .. getLayerSize()-1
//  * @param tick current BAM tick (4-Bit BAM has 16 ticks)
//  * @param shift current shift position
//  */
// void LightCube::transferLEDs(const int index, const int tick, int *shift)
// {
//     uint8_t transferByte = 0b00000000;

//     // ensure the layer index is between 0 (bottom) and layers-1 (top)
//     // evaluate the index of the last led in current (start) and previous layer (end).
//     int startIndex = (((index % getLayerSize()) + 1) * ((getRowSize() * getColSize())) - 1);
//     int endIndex = startIndex - (getRowSize() * getColSize());

//     // The idea is to shift out the led information from back to front from the perspective of the
//     // daisy chained shift registers. Shift out only the current layer for the current tick given by
//     // the BAM duty cycle. The rest is done by Arduino by repetetive calls of this method.

//     // now we have to shift out each LED from highest to lowest in the order blue, green, red
//     for (int i = startIndex; i > endIndex; i--)
//     {
//         // get brightnesses of led at index i
//         shiftAndTransferLedColor(tick, this->frame.getBlue(i), shift, &transferByte);
//         shiftAndTransferLedColor(tick, this->frame.getGreen(i), shift, &transferByte);
//         shiftAndTransferLedColor(tick, this->frame.getRed(i), shift, &transferByte);
//     }

//     // Shift out the layer anodes, the logic bases on the idea that the anodes are at the
//     // beginning of the daisy chained shift registers and that the bottem layer is
//     // connected in first position (MSBFIRST)
//     for (int i = getLayerSize() - 1; i >= 0; i--)
//     {
//         if (i == index)
//         {
//             transferByte = transferByte | (1 << *shift);
//         }
//         *shift = *shift - 1;
//     }

//     shiftToSPI(shift, &transferByte);
// }

// void LightCube::shiftAndTransferLedColor(const int tick, const Brightness brightness, int *shift, uint8_t *transferByte)
// {
//     // When tick contains the brightness then the led color pin is on;
//     // otherwise it is off. This ensures the 4 bit BAM.
//     if (((uint8_t)brightness) - (1 << tick) >= 0)
//     {
//         *transferByte = *transferByte | (1 << *shift);
//     }
//     else
//     {
//         *transferByte = *transferByte | (0 << *shift);
//     }
//     *shift = *shift - 1;

//     shiftToSPI(shift, transferByte);
// }

// void LightCube::shiftToSPI(int *shift, uint8_t *transferByte)
// {
//     // is byte ready to transfer
//     if (*shift < 0)
//     {
//         // Serial.print(*transferByte, BIN);
//         SPI.transfer(*transferByte);

//         // prepare for next byte to shift
//         *transferByte = 0b00000000;
//         *shift = 7;
//     }
// }

void LightCube::prepareNextDutyCycle() {
    // decrement the lifetime of current frame 
    this->frame.decrementLifeCycle();
}