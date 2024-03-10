#include "Graphics.h"
#include "Vector.h"
#include "LightCube.h"
#include "Frame.h"
#include "MemoryFree.h"
#include "VectorMath.h"
#include "fpVector3.h"

void Graphics::drawColumn(const int column, Coloring& coloring)
{
    // ensure column is in range
    if (0 > column || column >= (LightCube::getInstance().getRowSize() * LightCube::getInstance().getColSize()))
    {
        return;
    }

    // get the voxel for the column index
    for (int i = 0; i < LightCube::getInstance().getLayerSize(); i++) // z
    {

        int ledIndex = column + (LightCube::getInstance().getRowSize() * LightCube::getInstance().getColSize() * i);
        Voxel v = LightCube::getInstance().getFrame()->voxel(ledIndex);
        Color c = coloring.getColor(v);
        LightCube::getInstance().getFrame()->set(ledIndex, c.red, c.green, c.blue);
    }
}

void Graphics::drawLayer(const int layer, Coloring& coloring)
{
    if (layer < 0 || layer >= LightCube::getInstance().getLayerSize())
    {
        return;
    }

    int ledSize = LightCube::getInstance().getColSize() * LightCube::getInstance().getRowSize();
    int startLed = layer * ledSize;
    for (int i = 0; i < ledSize; i++)
    {
        Voxel v = LightCube::getInstance().getFrame()->voxel(i);
        Color c = coloring.getColor(v);        
        LightCube::getInstance().getFrame()->set(startLed + i, c.red, c.green, c.blue);
    }
}

void Graphics::drawColumn(const int column, const Color color, const long millis)
{
    // ensure column is in range
    if (0 > column || column >= (LightCube::getInstance().getRowSize() * LightCube::getInstance().getColSize()))
    {
        return;
    }

    // get the voxel for the column index
    for (int i = 0; i < LightCube::getInstance().getLayerSize(); i++)
    {
        int ledIndex = column + (LightCube::getInstance().getRowSize() * LightCube::getInstance().getColSize() * i);
        LightCube::getInstance().getFrame()->setPrepare();
        LightCube::getInstance().getFrame()->set(ledIndex, color.red, color.green, color.blue);
        LightCube::getInstance().getFrame()->activate(2);
        while (LightCube::getInstance().isBusy())
        { /* just wait till cube is ready to prepare next frame */
        }
    }
}

void Graphics::drawLine(Voxel voxel, Vector3D direction, Coloring &coloring)
{
}

void Graphics::drawLine(Voxel voxel, Vector3D direction, Coloring &coloring, long millis)
{
}

void Graphics::drawSphere(float size, Coloring &coloring, Frame *frame)
{
    // start with blank screen
    frame->setAllOff();
    drawSphere(size > 7 ? 7 : size, 3.5, 3.5, 3.5, coloring, frame);
}

void Graphics::drawSphere(float size, float mx, float my, float mz, Coloring &coloring, Frame *frame)
{
    // size of cube represents the radius max 3.5
    float r = (double)size / (double)2;

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
            Voxel next = Voxel(x, y, z);

            // avoid duplicate setting of voxels
            if (p != next)
            {
                Color c = coloring.getColor(next);
                frame->set(next.x, next.y, next.z, c.red, c.green, c.blue);
                p = next;
            }
        }
    }
}

void Graphics::drawRectangle(const Voxel *voxel, Direction a, Direction b, const int lengthA, const int lengthB, Coloring &coloring, Frame *frame)
{
    Vector3D aDir = Vector3D::getStandardBaseVector(a);
    Vector3D bDir = Vector3D::getStandardBaseVector(b);
    Voxel p = Voxel();
    Color color = Color();
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < lengthA; j++)
        {
            p = *voxel + (aDir * j) + (bDir * i * (lengthB - 1));
            color = coloring.getColor(p);
            frame->set(p.x, p.y, p.z, color.red, color.green, color.blue);
        }
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < lengthB; j++)
        {
            p = *voxel + (bDir * j) + (aDir * i * (lengthA - 1));
            color = coloring.getColor(p);
            frame->set(p.x, p.y, p.z, color.red, color.green, color.blue);
        }
    }
}

void Graphics::fillRectangle(Voxel voxel, Direction a, Direction b, int lengthA, int lenghtB, Coloring *coloring)
{
}

void Graphics::rotate(Direction direction, float degree, long frameTime)
{
    // Serial.println(F("Graphics start rotation"));
    // max diameter of the 8x8x8 cube is 7 and therefore a radius of 3.5
    // to move 360 degree the cube needs 28 steps at he outer ring
    // the inner ring needs just 4 steps
    int total = 28;
    int steps = round(total * degree / 360);

    fpVector3 k = fpVector3::getUnitVector(direction);
    Frame *f = LightCube::getInstance().getFrame();

    for (int i = 0; i < steps; i++)
    {
        f->setPrepare();
        f->setAllOff();
        // double start = millis();
        for (int j = 0; j < 512; j++)
        {
            Voxel vox = f->voxel(j);
            uint16_t rgbVal = f->get(j);
            if (rgbVal != 0)
            {
                // vox.print();
                Voxel vrot = VectorMath::axisAngleRotation(vox, k, i);
                // vrot.print();
                f->set(vrot.x, vrot.y, vrot.z, getColorValue(0, rgbVal), getColorValue(4, rgbVal), getColorValue(8, rgbVal));
                // Serial.println();
            }
        }
        // Serial.print(F("step time in ms "));
        // Serial.println(millis() - start);
        // activate each step
        f->activate(toFrames(100));

        while (LightCube::getInstance().isBusy())
        { /* wait */
        }
    }

}

void Graphics::erase()
{
    LightCube::getInstance().getFrame()->setAllOff();
}

int Graphics::toFrames(long millis)
{
    int frameRate = LightCube::getInstance().getFrameRate();
    float frameCount = frameRate * millis / 1000;
    return (int)max(round(frameCount), 1);
}

Voxel Graphics::rodRot(double sinTheta, double cosTheta, Voxel vox, Vector3D k)
{
    int16_t rx, ry, rz, dx, dy, dz, krx, kry, krz;
    int16_t vx, vy, vz, kx, ky, kz, st, ct;
    int16_t accuracy = 100;

    st = round(sinTheta * accuracy);
    ct = round(cosTheta * accuracy);

    vx = ((float)vox.x - 3.5) * accuracy;
    vy = ((float)vox.y - 3.5) * accuracy;
    vz = ((float)vox.z - 3.5) * accuracy;

    kx = round(k.x * accuracy);
    ky = round(k.y * accuracy);
    kz = round(k.z * accuracy);

    int16_t kvdot = fpmult(kx, vx, accuracy) + fpmult(ky, vy, accuracy) + fpmult(kz, vz, accuracy);

    dx = fpmult(kx, kvdot, accuracy);
    dy = fpmult(ky, kvdot, accuracy);
    dz = fpmult(kz, kvdot, accuracy);

    rx = vx - dx;
    ry = vy - dy;
    rz = vz - dz;

    // k cross r
    krx = (fpmult(ky, rz, accuracy)) - (fpmult(kz, ry, accuracy));
    kry = (fpmult(kz, rx, accuracy)) - (fpmult(kx, rz, accuracy));
    krz = (fpmult(kx, ry, accuracy)) - (fpmult(ky, rx, accuracy));

    krx = fpmult(krx, st, accuracy);
    kry = fpmult(kry, st, accuracy);
    krz = fpmult(krz, st, accuracy);

    rx = fpmult(rx, ct, accuracy);
    ry = fpmult(ry, ct, accuracy);
    rz = fpmult(rz, ct, accuracy);

    int x = round(((double)(dx + rx + krx) / (double)accuracy) + 3.5);
    int y = round(((double)(dy + ry + kry) / (double)accuracy) + 3.5);
    int z = round(((double)(dz + rz + krz) / (double)accuracy) + 3.5);

    return Voxel(x, y, z);
}

Voxel Graphics::rodRot2(double sinTheta, double cosTheta, Voxel vox, Vector3D k)
{
    int32_t dx, dy, dz, krx, kry, krz;
    int32_t vx, vy, vz, kx, ky, kz, st, ct;
    int32_t accuracy = 1000;

    st = round(sinTheta * accuracy);
    ct = round(cosTheta * accuracy);

    // vector displacement to coordinate origin
    vx = ((float)vox.x - 3.5) * accuracy;
    vy = ((float)vox.y - 3.5) * accuracy;
    vz = ((float)vox.z - 3.5) * accuracy;

    kx = round(k.x * accuracy);
    ky = round(k.y * accuracy);
    kz = round(k.z * accuracy);

    int32_t kvdot = fpmult(kx, vx, accuracy) + fpmult(ky, vy, accuracy) + fpmult(kz, vz, accuracy);

    dx = fpmult(kx, kvdot, accuracy);
    dy = fpmult(ky, kvdot, accuracy);
    dz = fpmult(kz, kvdot, accuracy);

    dx = fpmult(kx, (accuracy - ct), accuracy);
    dy = fpmult(ky, (accuracy - ct), accuracy);
    dz = fpmult(kz, (accuracy - ct), accuracy);

    // k cross v
    krx = (fpmult(ky, vz, accuracy)) - (fpmult(kz, vy, accuracy));
    kry = (fpmult(kz, vx, accuracy)) - (fpmult(kx, vz, accuracy));
    krz = (fpmult(kx, vy, accuracy)) - (fpmult(ky, vx, accuracy));

    krx = fpmult(krx, st, accuracy);
    kry = fpmult(kry, st, accuracy);
    krz = fpmult(krz, st, accuracy);

    vx = fpmult(vx, ct, accuracy);
    vy = fpmult(vy, ct, accuracy);
    vz = fpmult(vz, ct, accuracy);

    // vector displacement to the center of the cube
    int x = round(((double)(dx + vx + krx) / (double)accuracy) + 3.5);
    int y = round(((double)(dy + vy + kry) / (double)accuracy) + 3.5);
    int z = round(((double)(dz + vz + krz) / (double)accuracy) + 3.5);

    return Voxel(x, y, z);
}

long Graphics::fpmult(long a, long b, long accuracy)
{
    return (a * b) / accuracy;
}

uint8_t Graphics::getColorValue(uint8_t index, uint16_t value)
{
    uint8_t cval = 0b0000;
    bitWrite(cval, 0, bitRead(value, index++));
    bitWrite(cval, 1, bitRead(value, index++));
    bitWrite(cval, 2, bitRead(value, index++));
    bitWrite(cval, 3, bitRead(value, index));
    return cval;
}
