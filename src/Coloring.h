#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef Coloring_h
#define Coloring_h

#include "Color.h"
#include "Voxel.h"

class Coloring
{
public:
    virtual ~Coloring() = default;
    virtual Color getColor(const Voxel &vox) = 0;
    virtual Color getColor(uint8_t voxelX, uint8_t voxelY, uint8_t voxelZ) = 0;
};

class SolidColoring : public Coloring
{
public:
    SolidColoring();
    SolidColoring(Color *c);
    ~SolidColoring();
    void setColor(const Color &c);

    Color getColor(const Voxel &vox);

    Color getColor(uint8_t voxelX, uint8_t voxelY, uint8_t voxelZ);

private:
    Color *_c;
};

class ColorSpace : public Coloring
{
public:
    ColorSpace();
    ColorSpace(int width, int depth, int height);
    ~ColorSpace(){};
    Color getColor(const Voxel &vox);
    Color getColor(uint8_t voxelX, uint8_t voxelY, uint8_t voxelZ);
    void print();

private:
    int width, depth, height;
    Brightness red(const Voxel &vox);
    Brightness green(const Voxel &vox);
    Brightness blue(const Voxel &vox);
    Brightness colorSpace(const int i);
};

#endif