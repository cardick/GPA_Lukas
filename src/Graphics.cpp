#include "Graphics.h"
#include "LightCube.h"
#include "Frame.h"
#include "MathUtil.h"
#include "Vector.h"
#include "MemoryFree.h"

void Graphics::drawColumn(const int column, Coloring& coloring)
{
    uint8_t size = LightCube::getInstance().getRowSize() * LightCube::getInstance().getColSize();

    // ensure column is in range
    if (0 > column || column >= (size))
    {
        return;
    }

    // get the voxel for the column index
    for (int i = 0; i < LightCube::getInstance().getLayerSize(); i++)
    {
        int ledIndex = column + (size * i);
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
    uint8_t size = LightCube::getInstance().getRowSize() * LightCube::getInstance().getColSize();
    // ensure column is in range
    if (0 > column || column >= size)
    {
        return;
    }

    // get the voxel for the column index
    for (int i = 0; i < LightCube::getInstance().getLayerSize(); i++)
    {
        int ledIndex = column + (size * i);
        LightCube::getInstance().getFrame()->setPrepare();
        LightCube::getInstance().getFrame()->set(ledIndex, color.red, color.green, color.blue);
        LightCube::getInstance().getFrame()->activate(2);
        while (LightCube::getInstance().isBusy())
        { /* just wait till cube is ready to prepare next frame */
        }
    }
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

void Graphics::drawRectangle(uint8_t px, uint8_t py, uint8_t pz, Direction a, Direction b, const int lengthA, const int lengthB, Coloring &coloring, Frame *frame)
{
    int8_t ax = x_axis_value(a);
    int8_t ay = y_axis_value(a);
    int8_t az = z_axis_value(a);
    int8_t bx = x_axis_value(b);
    int8_t by = y_axis_value(b);
    int8_t bz = z_axis_value(b);

    uint8_t rpx, rpy, rpz;
    
    Color color = Color();
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < lengthA; j++)
        {
            rpx = px + (ax * j) + (bx * i * (lengthB - 1));
            rpy = py + (ay * j) + (by * i * (lengthB - 1));
            rpz = pz + (az * j) + (bz * i * (lengthB - 1));
            color = coloring.getColor(px, py, pz);
            frame->set(rpx, rpy, rpz, color.red, color.green, color.blue);
        }
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < lengthB; j++)
        {
            rpx = px + (bx * j) + (ax * i * (lengthA - 1));
            rpy = py + (by * j) + (ay * i * (lengthA - 1));
            rpz = pz + (bz * j) + (az * i * (lengthA - 1));
            color = coloring.getColor(px, py, pz);
            frame->set(rpx, rpy, rpz, color.red, color.green, color.blue);
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

void Graphics::print(float x, float y, float z)
{
    Serial.print(F("(x: "));
    Serial.print(x, 2);
    Serial.print(F(", y: "));
    Serial.print(y, 2);
    Serial.print(F(", z: "));
    Serial.print(z, 2);
    Serial.println(F(")"));
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
