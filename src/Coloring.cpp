#include "Coloring.h"

void SolidColoring::setColor(Color c)
{
    this->_c = c;
}

Color SolidColoring::getColor()
{
    return this->_c;
}