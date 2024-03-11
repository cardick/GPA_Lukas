#include "DataStore.h"

#include <SPI.h>
#include "Voxel.h"

DataStore::DataStore()
{
}

const uint8_t DataStore::getRows() const
{
    return ROWS;
}

const uint8_t DataStore::getCols() const
{
    return COLS;
}

const uint8_t DataStore::getLayers() const
{
    return LAYERS;
}

void DataStore::setAllOn(bool force)
{
    if (!isDirty)
    {
        isDirty = true;
    }

    memset(layeredStoreDirty, pgm_read_byte(&ALL_ON), LAYERS * BAM * BYTES);

    // correct the offset bits, that are not in use
    int offset = (ROWS * COLS) % 8;
    if (offset > 0)
    {
        for (int i = 0; i < LAYERS; i++)
        {
            for (int j = 0; j < BAM; j++)
            {
                for (int k = (8 - offset); k < 8; k++)
                {
                    bitWrite(layeredStoreDirty[i][j][BYTES - 1], k, 0);
                }
            }
        }
    }

    if (force)
    {
        synchronize();
    }
}

void DataStore::setAllOff(bool force)
{
    if (!isDirty)
    {
        isDirty = true;
    }

    memset(layeredStoreDirty, pgm_read_byte(&ALL_OFF), LAYERS * BAM * BYTES);

    if (force)
    {
        synchronize();
    }
}

uint16_t DataStore::get(uint16_t index) const
{
    if (index >= (ROWS * COLS * LAYERS))
    {
        return 0;
    }

    // evaluate bit positions
    uint8_t layer = index / (ROWS * COLS);
    uint8_t startIndex = (index % (ROWS * COLS)) * 3 / 8;
    uint8_t startPos = (index % (ROWS * COLS)) * 3 % 8;
    uint8_t endPos = startPos + 2;
    uint8_t endIndex = endPos < 8 ? startIndex : startIndex + 1;
    endPos = endPos < 8 ? endPos : endPos - 8;
    uint8_t greenIndex = startPos == 7 ? endIndex : startIndex;
    uint8_t greenPos = startPos == 7 ? endPos - 1 : startPos + 1;

    // write the cathode bits
    uint16_t tmp = 
        (bitRead(layeredStore[layer][0][startIndex], startPos) << 0) |
        (bitRead(layeredStore[layer][1][startIndex], startPos) << 1) |
        (bitRead(layeredStore[layer][2][startIndex], startPos) << 2) |
        (bitRead(layeredStore[layer][3][startIndex], startPos) << 3) |
        (bitRead(layeredStore[layer][0][greenIndex], greenPos) << 4) |
        (bitRead(layeredStore[layer][1][greenIndex], greenPos) << 5) |
        (bitRead(layeredStore[layer][2][greenIndex], greenPos) << 6) |
        (bitRead(layeredStore[layer][3][greenIndex], greenPos) << 7) |
        (bitRead(layeredStore[layer][0][endIndex], endPos) << 8) |
        (bitRead(layeredStore[layer][1][endIndex], endPos) << 9) |
        (bitRead(layeredStore[layer][2][endIndex], endPos) << 10) |
        (bitRead(layeredStore[layer][3][endIndex], endPos) << 11);

    return tmp;
}

uint16_t DataStore::get(uint8_t x, uint8_t y, uint8_t z) const
{
    return get(getIndex(x, y, z));
}

void DataStore::set(uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
{
    if (index >= (ROWS * COLS * LAYERS))
    {
        return;
    }

    if (!isDirty)
    {
        isDirty = true;
    }

    int8_t layer = index / (ROWS * COLS);
    int8_t offset = index % (ROWS * COLS);
    int8_t startIndex = offset * 3 / 8;
    int8_t startPos = offset * 3 % 8;
    int8_t endPos = startPos + 2;
    int8_t endIndex = endPos < 8 ? startIndex : startIndex + 1;
    endPos = endPos < 8 ? endPos : endPos - 8;

    // write bytes for red cathode
    bitWrite(layeredStoreDirty[layer][0][startIndex], startPos, bitRead(red, 0));
    bitWrite(layeredStoreDirty[layer][1][startIndex], startPos, bitRead(red, 1));
    bitWrite(layeredStoreDirty[layer][2][startIndex], startPos, bitRead(red, 2));
    bitWrite(layeredStoreDirty[layer][3][startIndex], startPos, bitRead(red, 3));

    // write bytes for green cathode
    int8_t greenIndex = startPos == 7 ? endIndex : startIndex;
    int8_t greenPos = startPos == 7 ? endPos - 1 : startPos + 1;
    bitWrite(layeredStoreDirty[layer][0][greenIndex], greenPos, bitRead(green, 0));
    bitWrite(layeredStoreDirty[layer][1][greenIndex], greenPos, bitRead(green, 1));
    bitWrite(layeredStoreDirty[layer][2][greenIndex], greenPos, bitRead(green, 2));
    bitWrite(layeredStoreDirty[layer][3][greenIndex], greenPos, bitRead(green, 3));

    // write bytes for blue cathode
    bitWrite(layeredStoreDirty[layer][0][endIndex], endPos, bitRead(blue, 0));
    bitWrite(layeredStoreDirty[layer][1][endIndex], endPos, bitRead(blue, 1));
    bitWrite(layeredStoreDirty[layer][2][endIndex], endPos, bitRead(blue, 2));
    bitWrite(layeredStoreDirty[layer][3][endIndex], endPos, bitRead(blue, 3));
}

void DataStore::set(uint8_t x, uint8_t y, uint8_t z, uint8_t red, uint8_t green, uint8_t blue)
{
    uint16_t index = getIndex(x, y, z);
    set(index, red, green, blue);
}

Voxel DataStore::getVoxel(uint16_t index) const
{
    if (index >= (ROWS * COLS * LAYERS))
    {
        return Voxel();
    }

    uint8_t z = index / (ROWS * COLS);
    uint8_t x = (index % (ROWS * COLS)) / COLS;
    uint8_t y = (index % (ROWS * COLS)) % COLS;

    return Voxel(x, y, z);
}

const uint16_t DataStore::getIndex(uint8_t x, uint8_t y, uint8_t z) const
{
    if (x >= ROWS)
        return -1;
    if (y >= COLS)
        return -1;
    if (z >= LAYERS)
        return -1;

    uint16_t index = z * ROWS * COLS;
    index += x * ROWS;
    index += y;
    return index;
}

void DataStore::shiftLayerForTick(uint8_t layerIndex, uint8_t tick)
{
    uint8_t bamIndex = getBAM(tick);

    if (bamIndex == -1)
    {
        return;
    }

    for (int8_t i = BYTES - 1; i >= 0; i--)
    {
        // correcture for red, since I used the same resistor size for every
        // cathode switch in the circuit
        // if(tick == 1) {
        //     SPI.transfer(layeredStore[layerIndex][bamIndex][i] & gammaCorrect[i%3]);
        // } else {
        //     SPI.transfer(layeredStore[layerIndex][bamIndex][i]);
        // }
        SPI.transfer(layeredStore[layerIndex][bamIndex][i]);
    }
    SPI.transfer(pgm_read_byte(&LAYER[layerIndex]));
}

bool DataStore::changed()
{
    return isDirty;
}

void DataStore::synchronize()
{
    for (uint8_t i = 0; i < LAYERS; i++)
    {
        for (uint8_t j = 0; j < BAM; j++)
        {
            // Use memcpy to copy the entire block of memory
            memcpy(layeredStore[i][j], layeredStoreDirty[i][j], BYTES);
        }
    }
    isDirty = false;
}

uint8_t DataStore::getBAM(uint8_t tick)
{
    if (0b0 <= tick && tick <= 0b1)
    {
        return 0;
    }
    if (0b10 <= tick && tick <= 0b11)
    {
        return 1;
    }
    if (0b100 <= tick && tick <= 0b111)
    {
        return 2;
    }
    if (0b1000 <= tick && tick <= 0b1111)
    {
        return 3;
    }
    return -1;
}