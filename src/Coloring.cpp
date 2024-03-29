#include "Coloring.h"

SolidColoring::SolidColoring() : _c(new Color())
{
}

SolidColoring::SolidColoring(Color *c) : _c(c)
{
}

SolidColoring::~SolidColoring()
{
    delete _c;
}

void SolidColoring::setColor(const Color &c)
{
    *(_c) = c;
    // this->_c->red = c.red;
    // this->_c->green = c.green;
    // this->_c->blue = c.blue;
}

Color SolidColoring::getColor(const Voxel &vox)
{
    return *_c;
}

Color SolidColoring::getColor(uint8_t voxelX, uint8_t voxelY, uint8_t voxelZ)
{
    return *_c;
}

ColorSpace::ColorSpace() : width(8), depth(8), height(8)
{
}

ColorSpace::ColorSpace(int width, int depth, int height) : width(width), depth(depth), height(height)
{
}

Color ColorSpace::getColor(const Voxel& vox)
{
    return Color(red(vox), green(vox), blue(vox));
}

Color ColorSpace::getColor(uint8_t voxelX, uint8_t voxelY, uint8_t voxelZ)
{
    Brightness red = colorSpace(static_cast<int>(round(4.0f / static_cast<float>(width) * static_cast<float>(voxelX))));
    Brightness green = colorSpace(static_cast<int>(round(4.0f / static_cast<float>(depth) * static_cast<float>(voxelY))));
    Brightness blue = colorSpace(static_cast<int>(round(4.0f / static_cast<float>(height) * static_cast<float>(voxelZ))));
    return Color(red, green, blue);
}

Brightness ColorSpace::red(const Voxel& vox)
{
    int i = static_cast<int>(round(4.0 / static_cast<float>(width) *  static_cast<float>(vox.x)));
    return colorSpace(i);
}

Brightness ColorSpace::green(const Voxel& vox)
{
    int i = static_cast<int>(round(4.0 / static_cast<float>(depth) * static_cast<float>(vox.y)));
    return colorSpace(i);
}

Brightness ColorSpace::blue(const Voxel& vox)
{
    int i = static_cast<int>(round(4.0 / static_cast<float>(height) * static_cast<float>(vox.z)));
    return colorSpace(i);
}

Brightness ColorSpace::colorSpace(const int i)
{
   switch(i) 
    {
        case 0:
            return Off;
        case 1:
            return Low;
        case 2:
            return Medium;
        case 3:
            return High;
        case 4:
            return Full;
    }
    return Off;
}

void ColorSpace::print()
{
    Serial.print(F("Color Space of width: "));
    Serial.print(width);
    Serial.print(F(", depth: "));
    Serial.print(depth);
    Serial.print(F(", height: "));
    Serial.println(height);
}
