#include "DataStore.h"
#include <SPI.h>

DataStore::DataStore()
{
}

DataStore::~DataStore()
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
    if(!this->isDirty) {
        this->isDirty = true;
    }

    for (int i = 0; i < LAYERS; i++)
    {
        for (int j = 0; j < DS_BYTES; j++)
        {
            this->layeredStoreDirty[i][j] = ALL_ON;
        }  
    }

    // correct the offset bits, that are not in use
    int offset = (DS_BYTES) % 8;
    if(offset > 0) { 
        for (int i = 0; i < LAYERS; i++)
        {
            for (int j = (8-offset); j < 8; j++)
            {
                bitWrite(layeredStoreDirty[i][DS_BYTES-1], j, 0);
            }
        }
    }

    if(force) { synchronize(); }
}

void DataStore::setAllOff(bool force)
{
    if(!this->isDirty) { 
        this->isDirty = true;
    }

    for (int i = 0; i < LAYERS; i++)
    {
        for (int j = 0; j < DS_BYTES; j++)
        {
            this->layeredStoreDirty[i][j] = ALL_OFF;
        }
    }

    if(force) { synchronize(); }
}

uint16_t DataStore::get(uint16_t led)
{
    if(led >= (ROWS*COLS*LAYERS)) { return 0; }

    int layer = led / (ROWS*COLS);
    int startIndex = (led % (ROWS*COLS)) * 3 / 8;
    int startPos = (led % (ROWS*COLS)) * 3 % 8;
    int endPos = startPos + 2;
    int endIndex = endPos < 8 ? startIndex : startIndex + 1;
    endPos = endPos < 8 ? endPos : endPos - 8;
    
    uint16_t tmp = 0b000000000000;

    // write bytes for red cathode
    bitWrite(tmp, 0, bitRead(layeredStore[layer][0][startIndex], startPos));
    bitWrite(tmp, 1, bitRead(layeredStore[layer][0][startIndex], startPos));
    bitWrite(tmp, 2, bitRead(layeredStore[layer][1][startIndex], startPos));
    bitWrite(tmp, 3, bitRead(layeredStore[layer][2][startIndex], startPos));

    // write bytes for green cathode
    int greenIndex = startPos == 7 ? endIndex : startIndex;
    int greenPos = startPos == 7 ? endPos - 1 : startPos + 1;
    bitWrite(tmp, 4, bitRead(layeredStore[layer][0][greenIndex], greenPos));
    bitWrite(tmp, 5, bitRead(layeredStore[layer][0][greenIndex], greenPos));
    bitWrite(tmp, 6, bitRead(layeredStore[layer][1][greenIndex], greenPos));
    bitWrite(tmp, 7, bitRead(layeredStore[layer][2][greenIndex], greenPos));
    
    // write bytes for blue cathode
    bitWrite(tmp, 8, bitRead(layeredStore[layer][0][endIndex], endPos));
    bitWrite(tmp, 9, bitRead(layeredStore[layer][0][endIndex], endPos));
    bitWrite(tmp, 10, bitRead(layeredStore[layer][1][endIndex], endPos));
    bitWrite(tmp, 11, bitRead(layeredStore[layer][2][endIndex], endPos));

    return tmp;
}

uint16_t DataStore::get(uint8_t x, uint8_t y, uint8_t z)
{
    return get(getLedNumber(x,y,z));
}

void DataStore::set(uint16_t led, uint8_t red, uint8_t green, uint8_t blue)
{
    if(led >= (ROWS*COLS*LAYERS)) { return; }

    if(!this->isDirty) { this->isDirty = true; }

    int layer = led / (ROWS*COLS);
    int index = (led % (ROWS*COLS)) * 6 / 8;
    int pos = (led % (ROWS*COLS)) * 6 % 8;

    for (int i = 0; i < 6; i++)
    {
        uint8_t colorValue = 0b00;
        switch (i)
        {
        case 0:
        case 1:
            colorValue = get2BitColorValue(red);
            break;
        case 2:
        case 3:
            colorValue = get2BitColorValue(green);
            break;
        case 4:
        case 5:
            colorValue = get2BitColorValue(blue);
            break;
        }
        byte b = bitRead(colorValue, pos%2);
        bitWrite(layeredStoreDirty[layer][index], pos, b);
        if(pos == 7) {
            index++;
            pos = 0;
        } else {
            pos++;
        }
    }
}

void DataStore::set(uint8_t x, uint8_t y, uint8_t z, uint8_t red, uint8_t green, uint8_t blue)
{
    set(getLedNumber(x,y,z), red, green, blue);
}

const uint16_t DataStore::getLedNumber(uint8_t x, uint8_t y, uint8_t z)
{
    if(x >= COLS) return -1;
    if(y >= ROWS) return -1;
    if(z >= LAYERS) return -1;

    int ledNumber = ((z == 0) ? 0 : (z - 1) * (ROWS * COLS));
    ledNumber += (y == 0 ? 0 : (y - 1) * ROWS);
    ledNumber += x;
    return ledNumber;
}

// implementation is for 8x8x8 cube only
void DataStore::shiftLayerForTick(int layerIndex, int tick)
{
    int bamIndex = getBAM(tick);
    if(bamIndex == -1) { return; }

    for (int i = BYTES-1; i >= 0; i--)
    {
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

void DataStore::shiftLayerForTickToSerial(int layerIndex, int tick)
{
    int bamIndex = getBAM(tick);
    if(bamIndex == -1) { 
        Serial.print("Invalid BAM index ");
        Serial.print(bamIndex);
        Serial.print(" for tick ");
        Serial.println(tick);
        return; 
    } else {
        Serial.print("Shift BAM index ");
        Serial.print(bamIndex);
        Serial.print(" for tick ");
        Serial.println(tick);
    }

    // shift cathode settings
    for (int i = BYTES-1; i >= 0; i--)
    {
        shiftToSerial(layeredStore[layerIndex][bamIndex][i]);
    }

    // shift anode settings
    switch (layerIndex)
    {
        case 0:
            shiftToSerial(LAYER_1);
            break;
        case 1:
            shiftToSerial(LAYER_2);
            break;
        case 2:
            shiftToSerial(LAYER_3);
            break;
        case 3:
            shiftToSerial(LAYER_4);
            break;
        case 4:
            shiftToSerial(LAYER_5);
            break;
        case 5:
            shiftToSerial(LAYER_6);
            break;
        case 6:
            shiftToSerial(LAYER_7);
            break;
        case 7:
            shiftToSerial(LAYER_8);
            break;
    }
}

bool DataStore::changed()
{
    return this->isDirty;
}

void DataStore::synchronize()
{
    // Serial.println("[DS] sync");
    for (int i = 0; i < ROWS*COLS*LAYERS; i++)
    {
        uint8_t rgbValue = getRgbValue(i);
        copy(i, rgbValue);
    }
    this->isDirty = false;
    // Serial.println("[DS] sync end");
}

int DataStore::getBAM(int tick)
{
    if(0b0 <= tick && tick <=0b11) {
        return 0;
    }
    if(0b100 <= tick && tick <=0b111){
        return 1;
    }
    if(0b1000 <= tick && tick <= 0b1111){
        return 2;
    }
    return -1;
}

void DataStore::copy(int led, uint8_t rgbValue)
{
    int layer = led / (ROWS*COLS);
    int startIndex = (led % (ROWS*COLS)) * 3 / 8;
    int startPos = (led % (ROWS*COLS)) * 3 % 8;
    int endPos = startPos + 2;
    int endIndex = endPos < 8 ? startIndex : startIndex + 1;
    endPos = endPos < 8 ? endPos : endPos - 8;
    
    // write bytes for red cathode
    uint8_t colorValue = get2BitColorValue(Red, rgbValue);
    bitWrite(layeredStore[layer][0][startIndex], startPos, colorValue > 0 ? 1 : 0);
    bitWrite(layeredStore[layer][1][startIndex], startPos, colorValue > 1 ? 1 : 0);
    bitWrite(layeredStore[layer][2][startIndex], startPos, colorValue > 2 ? 1 : 0);

    // write bytes for green cathode
    colorValue = get2BitColorValue(Green, rgbValue);
    int greenIndex = startPos == 7 ? endIndex : startIndex;
    int greenPos = startPos == 7 ? endPos - 1 : startPos + 1;
    bitWrite(layeredStore[layer][0][greenIndex], greenPos, colorValue > 0 ? 1 : 0);
    bitWrite(layeredStore[layer][1][greenIndex], greenPos, colorValue > 1 ? 1 : 0);
    bitWrite(layeredStore[layer][2][greenIndex], greenPos, colorValue > 2 ? 1 : 0);

    // write bytes for blue cathode
    colorValue = get2BitColorValue(Blue, rgbValue);
    bitWrite(layeredStore[layer][0][endIndex], endPos, colorValue > 0 ? 1 : 0);
    bitWrite(layeredStore[layer][1][endIndex], endPos, colorValue > 1 ? 1 : 0);
    bitWrite(layeredStore[layer][2][endIndex], endPos, colorValue > 2 ? 1 : 0);
}

uint8_t DataStore::getRgbValue(int led)
{
    if(led >= (ROWS*COLS*LAYERS) || led < 0) { return 0; }

    int layer = led / (ROWS*COLS);
    int index = (led % (ROWS*COLS)) * 6 / 8;
    int pos = (led % (ROWS*COLS)) * 6 % 8;
    
    uint8_t tmp = 0b000000;

    for(int i = 0; i < 6; i++) {
        byte b = bitRead(layeredStoreDirty[layer][index], pos);
        bitWrite(tmp, i, b);
        if(pos == 7) {
            index++;
            pos = 0;
        } else {
            pos++;
        }
    }
    return tmp;
}

uint8_t DataStore::get4BitBam(uint8_t colorValue)
{
    switch (colorValue)
    {
    case 0b01:
        return 0b0011;
    case 0b10:
        return 0b0111;
    case 0b11:
        return 0b1111;
    default:
        return 0b0000;
    }
}

uint8_t DataStore::get2BitColorValue(uint8_t bamValue)
{
    switch (bamValue)
    {
    case 0b0001:
    case 0b0011:
        return 0b01;
    case 0b0111:
        return 0b10;
    case 0b1111:
        return 0b11;
    default:
        return 0b00;
    }
}

uint8_t DataStore::get2BitColorValue(RgbColor color, uint8_t rgbValue)
{
    uint8_t colorValue = 0b00;
    int index1, index2;
    switch (color)
    {
    case Red:
        index1 = 0;
        index2 = 1;
        break;
    case Green:
        index1 = 2;
        index2 = 3;
        break;
    case Blue:
        index1 = 4;
        index2 = 5;
        break;
    }

    bitWrite(colorValue, 0, bitRead(rgbValue, index1));
    bitWrite(colorValue, 1, bitRead(rgbValue, index2));

    return colorValue;
}

uint8_t DataStore::getValueForBamIndex(uint8_t rgbValue, int bamIndex)
{
    uint8_t tmp =  0b000;
    if(rgbValue == 0) { return tmp; }

    bitWrite(tmp, 0, isOn(get2BitColorValue(Red, rgbValue), bamIndex));
    bitWrite(tmp, 1, isOn(get2BitColorValue(Green, rgbValue), bamIndex));
    bitWrite(tmp, 2, isOn(get2BitColorValue(Blue, rgbValue), bamIndex));
    return tmp;
}

bool DataStore::isOn(uint8_t colorValue, int bamIndex)
{
    switch (bamIndex)
    {
        case 0:
        case 1:
            return colorValue >= 0b01;
        case 2:
            return colorValue >= 0b10;
        case 3:
            return colorValue == 0b11;
        default:
            return 0;
    }
}

inline void DataStore::shiftToSerial(uint8_t value)
{
    for (int i = 7; i >= 0; i--)
    {
        Serial.print(bitRead(value, i));
    }
    Serial.println();
}