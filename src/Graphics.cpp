#include "Graphics.h"
#include "Vector.h"
#include "LightCube.h"
#include "Frame.h"
#include "MemoryFree.h"

void Graphics::drawColumn(const int column, const Color color)
{
    // ensure column is in range
    if(0 > column || column >= (LightCube::getInstance().getRowSize() * LightCube::getInstance().getColSize())) { return; }

    // get the voxel for the column index
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

    // get the voxel for the column index
    for (int i = 0; i < LightCube::getInstance().getLayerSize(); i++)
    {
        int ledIndex = column + (LightCube::getInstance().getRowSize() * LightCube::getInstance().getColSize() * i);
        LightCube::getInstance().getFrame()->setPrepare();
        LightCube::getInstance().getFrame()->set(ledIndex, color.red, color.green, color.blue);
        LightCube::getInstance().getFrame()->activate(2);
        while (LightCube::getInstance().isBusy()) { /* just wait till cube is ready to prepare next frame */ }
    }
}

void Graphics::drawLine(Voxel voxel, Vector3D direction, Coloring &coloring)
{
}

void Graphics::drawLine(Voxel voxel, Vector3D direction, Coloring& coloring, long millis)
{
}

void Graphics::drawSphere(float size, Coloring& coloring, Frame *frame)
{
    // start with blank screen
    frame->setAllOff();
    drawSphere(size > 7 ? 7 : size, 3.5, 3.5, 3.5, coloring, frame);
}

void Graphics::drawSphere(float size, float mx, float my, float mz, Coloring& coloring, Frame *frame)
{
    // size of cube represents the radius max 3.5
    float r = (double)size/(double)2;

    // in the 8x8x8 cube the perimeter of the cube is 4x8 - 4 voxels
    int total = 28;
    Voxel p = Voxel();

    for (int i = 0; i < total; i++)
    {
        // map i to PI range to get the lon value
        float lon = projToRad(i, 0, total, -M_PI_2, M_PI_2);

        for (int j = 0; j < total; j++)
        {
            // map j to PI range to get the lat value
            float lat = projToRad(j, 0, total, -M_PI, M_PI);

            // calculate the offsets from center voxel M and add them to M's coordinates
            float x = round(mx + (r * sin(lon) * cos(lat)));
            float y = round(my + (r * sin(lon) * sin(lat)));
            float z = round(mz + (r * cos(lon)));

            // avoid duplicate setting of voxels
            if(p.x != x || p.y != y || p.z != z) {
                frame->set(x, y, z, coloring.getColor().red, coloring.getColor().green, coloring.getColor().blue);
                p.x = x;
                p.y = y;
                p.z = z;
            }
        }
    }
}

void Graphics::drawRectangle(const Voxel * voxel, Direction a, Direction b, const int lengthA, const int lengthB, Coloring& coloring, Frame *frame)
{
    Vector3D aDir = Vector3D::getUnitVector(a);
    Vector3D bDir = Vector3D::getUnitVector(b);

    Color color = coloring.getColor();
    Voxel p = Voxel();

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < lengthA; j++)
        {
            p.x = voxel->x + (aDir.x * j) + (bDir.x * i * (lengthB - 1));
            p.y = voxel->y + (aDir.y * j) + (bDir.y * i * (lengthB - 1));
            p.z = voxel->z + (aDir.z * j) + (bDir.z * i * (lengthB - 1));

            frame->set(
                p.x, 
                p.y,
                p.z,
                color.red, 
                color.green, 
                color.blue );
        }
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < lengthB; j++)
        {
            frame->set(
                voxel->x + (bDir.x * j) + (aDir.x * i * (lengthA - 1)), 
                voxel->y + (bDir.y * j) + (aDir.y * i * (lengthA - 1)),
                voxel->z + (bDir.z * j) + (aDir.z * i * (lengthA - 1)),
                color.red, 
                color.green, 
                color.blue );
        }
    }
}

void Graphics::fillRectangle(Voxel voxel, Direction a, Direction b, int lengthA, int lenghtB, Coloring *coloring)
{
}

void Graphics::rotate(Vector3D fromPlane, Vector3D toPlane)
{
    // 14 Steps
    // Vector3D dir = toPlane - fromPlane;
    // move to positive direction

    // move to negative direction
}

void Graphics::erase()
{
    LightCube::getInstance().getFrame()->setAllOff();
}
