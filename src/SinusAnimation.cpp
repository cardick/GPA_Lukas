#include "SinusAnimation.h"
#include "Coloring.h"
#include "MemoryFree.h"

SinusAnimation::SinusAnimation() : poleDirX(0), poleDirY(0), poleDirZ(0), refDirX(0), refDirY(0), refDirZ(0)
{
}

void SinusAnimation::run()
{
    run(0, 25);
}

void SinusAnimation::run(int variant, long runtime)
{
    wait();

    switch (variant)
    {
    case 1:
        runMultipleWaces(runtime);
        break;
    default:
        runSingleWave(runtime);
        break;
    }
}

void SinusAnimation::runSingleWave(long runtime)
{
    uint8_t offset = 4;
    uint8_t amplitude = 3;
    poleDirX = 0;
    poleDirY = 0;
    poleDirZ = 1;
    refDirX = 1;
    refDirY = 0;
    refDirZ = 0;
    uint16_t runs = runtime/40;

    for (uint16_t i = 0; i < runs; i++)
    {
        LightCube::getInstance().getFrame()->setPrepare();
        calculateSingleWaveFrame(offset, amplitude, i+1);
        LightCube::getInstance().getFrame()->activate(getFrameCount(runtime/runs));
        wait();
    }
}

void SinusAnimation::runMultipleWaces(long runtime)
{
    Vector3D pole = Vector3D(0,0,1); // pole
    Vector3D ref = Vector3D(0,1,0); // ref
    int offset = 4;
    double amplitude = 3;
    Frame * frame = LightCube::getInstance().getFrame();
    int runs = runtime/30;
    for (int i = 0; i < runs; i++)
    {
        frame->setPrepare();
        calculate(frame, &ref, &pole, offset, amplitude, i+1);
        frame->activate(getFrameCount(runtime/runs));
        wait();
    }
}


// all vectors can be replaced by int8_t x,y,z values - there are only operations on int values in a range of 0 .. 8
void SinusAnimation::calculateSingleWaveFrame(const uint8_t poleOffset, const uint8_t amplitude, const uint16_t shift)
{
    // TODO: these must be standard base vector and not unit vector

    LightCube::getInstance().getFrame()->setAllOff();

    uint8_t p2X=0, p2Y=0, p2Z=0;

    double curveCompress = 0.5;
    int8_t stepSize = 15;
    int8_t lastValue = 0;

    for(int8_t i = 0; i < 8; i++) {
        // set ref coordinate to zero
        resetReferenceDirectionValue(&p2X, &p2Y, &p2Z);

        for (int8_t j = 7; j >= 0; j--)
        {
            // calc sinus value based on shift and current j value
            uint16_t deg = (((shift + j) % (360/stepSize))) * stepSize;
            int8_t sinus = sinValue(deg, curveCompress, amplitude);

            // set pole coordinate to zero
            resetPoleDirectionValue(&p2X, &p2Y, &p2Z);

            // set new pole coordinate
            uint8_t sinusOffset = poleOffset + sinus;
            p2X += poleDirX * sinusOffset;
            p2Y += poleDirY * sinusOffset;
            p2Z += poleDirZ * sinusOffset;

            // get color for point depending on the reference direction (claculated by dot product)
            int8_t poleDotP2 = (poleDirX*p2X) + (poleDirY*p2Y) + (poleDirZ*p2Z);
            Color color = getColor(lastValue <= poleDotP2);
            lastValue = poleDotP2;
            
            // set point to frame
            LightCube::getInstance().getFrame()->set(p2X, p2Y, p2Z, color.red, color.green, color.blue);

            // increment ref coordinate
            p2X += refDirX;
            p2Y += refDirY;
            p2Z += refDirZ;

        }
        // increment plane coordinate
        incrementByPlane(&p2X, &p2Y, &p2Z);
    }
}

void SinusAnimation::calculate(Frame * frame, const Vector3D * referenceDirection, const Vector3D * poleDirection, const int poleOffset, const double amplitude, const int shift)
{
    if(!referenceDirection->isUnitVector() || !poleDirection->isUnitVector()) { return; }
    frame->setAllOff();

    // eval the third direction
    Vector3D plane = Vector3D(1,1,1) - *poleDirection;
    plane -= *referenceDirection;

    // prepare vectors to reset the specific coordinates 
    Vector3D refReset = Vector3D(1,1,1) - *referenceDirection;
    Vector3D poleReset = Vector3D(1,1,1) - *poleDirection;

    Voxel p2 = Voxel();

    double radian = 0.0;
    double curveCompress = 1;
    int stepSize = 15;
    
    for(int i = 0; i < 8; i++) {
        // set ref coordinate to zero
        p2 = p2 * refReset;

        for (int j = 0; j < 8; j++)
        {
            // calc sinus value based on shift and current j value
            radian = M_PI * (((shift + j) % stepSize) + 1) * stepSize / 180;
            double compression = curveCompress + ((i+1)%2 > 0 ? 0.5/(i+1) : -0.5/(i+1));
            int sinValue = round(amplitude * sin(compression * radian - (M_PI / (i>4 ? i%4 - 4 : i%4 + 1))));

            // set pole coordinate to zero
            p2 = p2 * poleReset;
            // set new pole coordinate
            p2 += *poleDirection * (poleOffset + sinValue);

            // get color for point depending on the reference direction
            Color color = getColor((int)((plane.x*p2.x)+(plane.y*p2.y)+(plane.z*p2.z)));
            
            // set point to frame
            frame->set(p2.x, p2.y, p2.z, color.red, color.green, color.blue);

            // increment ref coordinate
            p2 += *referenceDirection;
        }

        // increment plane coordinate
        p2 += plane;
    }
}

int8_t SinusAnimation::sinValue(int16_t degrees, float compress, float amplitude)
{
    // calc sinus value based on shift and current j value
    double radian = static_cast<double>(M_PI * degrees / 180);
    double compression = static_cast<double>(compress + 1.0 / M_PI_4);
    double sinValue = amplitude * sin(compression * radian);
    return static_cast<int8_t>(round(sinValue));
}

Color SinusAnimation::getColor(int i)
{
    Color color = Color();

    switch (i)
    {
    case 0:
        color.red = Medium;
        color.green = Off;
        color.blue = High;
        break;
    case 1:
        color.red = High;
        color.green = Off;
        color.blue = High;
        break;
    case 2:
        color.red = High;
        color.green = Off;
        color.blue = Medium;
        break;
    case 3:
        color.red = High;
        color.green = Off;
        color.blue = Off;
        break;
    case 4:
        color.red = High;
        color.green = High;
        color.blue = Off;
        break;
    case 5:
        color.red = Medium;
        color.green = High;
        color.blue = Off;
        break;
    case 6:
        color.red = Off;
        color.green = High;
        color.blue = Off;
        break;
    case 7:
        color.red = Off;
        color.green = High;
        color.blue = Medium;
        break;
    default:
        break;
    }
    return color;
}

Color SinusAnimation::getColor(bool dropping)
{
    Color tmp = Color();
    if(dropping) {
        tmp.red = Brightness::Off;
        tmp.green = Brightness::Low;
        tmp.blue = Brightness::Low;
    } else {
        tmp.red = Brightness::Off;
        tmp.green = Brightness::Full;
        tmp.blue = Brightness::Full;
    }
    return tmp;
}

void SinusAnimation::resetReferenceDirectionValue(uint8_t *px, uint8_t *py, uint8_t *pz)
{
    *px *= (1 - refDirX);
    *py *= (1 - refDirY);
    *pz *= (1 - refDirZ);
}

void SinusAnimation::resetPoleDirectionValue(uint8_t *px, uint8_t *py, uint8_t *pz)
{
    *px *= (1 - poleDirX);
    *py *= (1 - poleDirY);
    *pz *= (1 - poleDirZ);
}

void SinusAnimation::incrementByPlane(uint8_t *px, uint8_t *py, uint8_t *pz)
{
    *px += (1 - poleDirX - refDirX);
    *py += (1 - poleDirY - refDirY);
    *pz += (1 - poleDirZ - refDirZ);
}
