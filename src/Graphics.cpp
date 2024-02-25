#include "Graphics.h"
#include "Vector.h"
#include "LightCube.h"

void Graphics::drawColumn(const int column, const Color color)
{
    // ensure column is in range
    if(0 > column || column >= (LightCube::getInstance().getRowSize() * LightCube::getInstance().getColSize())) { return; }
    // Serial.println("[Graphics] begin drawing");

    // get the point for the column index
    for (int i = 0; i < LightCube::getInstance().getLayerSize(); i++)
    {
        int ledIndex = column + (LightCube::getInstance().getRowSize() * LightCube::getInstance().getColSize() * i);
        LightCube::getInstance().getFrame()->set(ledIndex, color.red, color.green, color.blue);
    }
}

void Graphics::drawLayer(const int layer, const Color color)
{
    if(layer < 0 || layer >= LightCube::getInstance().getLayerSize()) {return; }

    int ledSize = LightCube::getInstance().getColSize() * LightCube::getInstance().getRowSize();
    int startLed = layer * ledSize;
    for(int i = 0; i < ledSize; i++) 
    {
        LightCube::getInstance().getFrame()->set(startLed + i, color.red, color.green, color.blue);
    }
}

void Graphics::drawColumn(const int column, const Color color, const long millis)
{
    // ensure column is in range
    if(0 > column || column >= (LightCube::getInstance().getRowSize() * LightCube::getInstance().getColSize())) { return; }
    // Serial.println("[Graphics] begin drawing");

    // get the point for the column index
    for (int i = 0; i < LightCube::getInstance().getLayerSize(); i++)
    {
        int ledIndex = column + (LightCube::getInstance().getRowSize() * LightCube::getInstance().getColSize() * i);
        LightCube::getInstance().getFrame()->setPrepare();
        LightCube::getInstance().getFrame()->set(ledIndex, color.red, color.green, color.blue);
        LightCube::getInstance().getFrame()->activate(2);
        // Serial.println("[Graphics] waiting for cube");
        while (LightCube::getInstance().isBusy()) { /* just wait till cube is ready to prepare next frame */ }
        // Serial.println("[Graphics] wake up");
    }
}

void Graphics::drawLine(Point3D point, Vector3D direction, Coloring &coloring)
{
}

void Graphics::drawLine(Point3D point, Vector3D direction, Coloring& coloring, long millis)
{
}

void Graphics::drawRectangle(Point3D point, Direction a, Direction b, int lengthA, int lenghtB, Coloring * coloring)
{
}

void Graphics::fillRectangle(Point3D point, Direction a, Direction b, int lengthA, int lenghtB, Coloring *coloring)
{
}

void Graphics::erase()
{
}
