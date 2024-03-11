#include "DataStore.h"
#include <SPI.h>
#include "Vector.h"

DataStore::DataStore()
{
}

const int DataStore::getRows()
{
    return ROWS;
}

const int DataStore::getCols()
{
    return COLS;
}

const int DataStore::getLayers()
{
    return LAYERS;
}

void DataStore::setAllOn(bool force)
{
    if (!this->isDirty)
    {
        this->isDirty = true;
    }

    for (int i = 0; i < LAYERS; i++)
    {
        for (int j = 0; j < BAM; j++)
        {
            for (int k = 0; k < BYTES; k++)
            {
                this->layeredStoreDirty[i][j][k] = ALL_ON;
            }
        }
    }

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
    if (!this->isDirty)
    {
        this->isDirty = true;
    }

    for (int i = 0; i < LAYERS; i++)
    {
        for (int j = 0; j < BAM; j++)
        {
            for (int k = 0; k < BYTES; k++)
            {
                this->layeredStoreDirty[i][j][k] = ALL_OFF;
            }
        }
    }

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

    int layer = index / (ROWS * COLS);
    int startIndex = (index % (ROWS * COLS)) * 3 / 8;
    int startPos = (index % (ROWS * COLS)) * 3 % 8;
    int endPos = startPos + 2;
    int endIndex = endPos < 8 ? startIndex : startIndex + 1;
    endPos = endPos < 8 ? endPos : endPos - 8;

    uint16_t tmp = 0b000000000000;

    // write bytes for red cathode
    bitWrite(tmp, 0, bitRead(layeredStore[layer][0][startIndex], startPos));
    bitWrite(tmp, 1, bitRead(layeredStore[layer][1][startIndex], startPos));
    bitWrite(tmp, 2, bitRead(layeredStore[layer][2][startIndex], startPos));
    bitWrite(tmp, 3, bitRead(layeredStore[layer][3][startIndex], startPos));

    // write bytes for green cathode
    int greenIndex = startPos == 7 ? endIndex : startIndex;
    int greenPos = startPos == 7 ? endPos - 1 : startPos + 1;
    bitWrite(tmp, 4, bitRead(layeredStore[layer][0][greenIndex], greenPos));
    bitWrite(tmp, 5, bitRead(layeredStore[layer][1][greenIndex], greenPos));
    bitWrite(tmp, 6, bitRead(layeredStore[layer][2][greenIndex], greenPos));
    bitWrite(tmp, 7, bitRead(layeredStore[layer][3][greenIndex], greenPos));

    // write bytes for blue cathode
    bitWrite(tmp, 8, bitRead(layeredStore[layer][0][endIndex], endPos));
    bitWrite(tmp, 9, bitRead(layeredStore[layer][1][endIndex], endPos));
    bitWrite(tmp, 10, bitRead(layeredStore[layer][2][endIndex], endPos));
    bitWrite(tmp, 11, bitRead(layeredStore[layer][3][endIndex], endPos));

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

    if (!this->isDirty)
    {
        this->isDirty = true;
    }

    int layer = index / (ROWS * COLS);
    int startIndex = (index % (ROWS * COLS)) * 3 / 8;
    int startPos = (index % (ROWS * COLS)) * 3 % 8;
    int endPos = startPos + 2;
    int endIndex = endPos < 8 ? startIndex : startIndex + 1;
    endPos = endPos < 8 ? endPos : endPos - 8;

    // write bytes for red cathode
    bitWrite(layeredStoreDirty[layer][0][startIndex], startPos, bitRead(red, 0));
    bitWrite(layeredStoreDirty[layer][1][startIndex], startPos, bitRead(red, 1));
    bitWrite(layeredStoreDirty[layer][2][startIndex], startPos, bitRead(red, 2));
    bitWrite(layeredStoreDirty[layer][3][startIndex], startPos, bitRead(red, 3));

    // write bytes for green cathode
    int greenIndex = startPos == 7 ? endIndex : startIndex;
    int greenPos = startPos == 7 ? endPos - 1 : startPos + 1;
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

Voxel DataStore::getVoxel(int index) const
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

    int index = z * ROWS * COLS;
    index += x * ROWS;
    index += y;
    return index;
}

void DataStore::shiftLayerForTick(int layerIndex, int tick)
{
    int bamIndex = getBAM(tick);
    if (bamIndex == -1)
    {
        return;
    }

    for (int i = BYTES - 1; i >= 0; i--)
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

    switch (layerIndex)
    {
    case 0:
        SPI.transfer(LAYER_1);
        break;
    case 1:
        SPI.transfer(LAYER_2);
        break;
    case 2:
        SPI.transfer(LAYER_3);
        break;
    case 3:
        SPI.transfer(LAYER_4);
        break;
    case 4:
        SPI.transfer(LAYER_5);
        break;
    case 5:
        SPI.transfer(LAYER_6);
        break;
    case 6:
        SPI.transfer(LAYER_7);
        break;
    case 7:
        SPI.transfer(LAYER_8);
        break;
    }
}

bool DataStore::changed()
{
    return this->isDirty;
}

void DataStore::synchronize()
{
    for (int i = 0; i < LAYERS; i++)
    {
        for (int j = 0; j < BAM; j++)
        {
            for (int k = 0; k < BYTES; k++)
            {
                layeredStore[i][j][k] = layeredStoreDirty[i][j][k];
            }
        }
    }
    this->isDirty = false;
}

int DataStore::getBAM(int tick)
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