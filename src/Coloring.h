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
    virtual Color getColor(const Voxel& vox) = 0;
};

class SolidColoring : public Coloring
{
public:
    void setColor(Color c);

    Color getColor(const Voxel& vox);

private:
    Color _c;
};

class ColorSpace : public Coloring
{
public:
    ColorSpace();
    ColorSpace(int width, int depth, int height);
    Color getColor(const Voxel& vox);
    void print();

private:
    int width, depth, height;
    Brightness red(const Voxel& vox);
    Brightness green(const Voxel& vox);
    Brightness blue(const Voxel& vox);
    Brightness colorSpace(const int i);
};

#endif