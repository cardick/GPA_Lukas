#include "SinusAnimation.h"
#include "Coloring.h"
#include "MemoryFree.h"

void SinusAnimation::run()
{
    run(0, 25);
}

void SinusAnimation::run(int variant, long millis)
{
    wait();
    Vector3D pole;
    Vector3D ref;
    int offset = 4;
    double amplitude = 3;
    Frame * frame = LightCube::getInstance().getFrame();
    int runs = 0;
    switch (variant)
    {
    case 1:
        pole = Vector3D(0,0,1); // pole
        ref = Vector3D(0,1,0); // ref
        runs = millis/30;
        break;
    default:
        pole = Vector3D(0,0,1); // pole
        ref = Vector3D(1,0,0); // ref
        runs = millis/40;
        break;
    }

    for (int i = 0; i < runs; i++)
    {
        frame->setPrepare();
        switch (variant)
        {
        case 1:
            calculate(frame, &ref, &pole, offset, amplitude, i+1);
            break;
        default:
            calculateSingle(frame, &ref, &pole, offset, amplitude, i+1);
            break;
        }
        frame->activate(getFrameCount(millis/runs));
        wait();
    }
}

void SinusAnimation::calculateSingle(Frame * frame, const Vector3D * referenceDirection, const Vector3D * poleDirection, const int poleOffset, const double amplitude, const int shift)
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
    double lastValue = 0;

    for(int i = 0; i < 8; i++) {
        // set ref coordinate to zero
        p2 = p2 * refReset;
        for (int j = 7; j >= 0; j--)
        {
            // calc sinus value based on shift and current j value
            radian = M_PI * (((shift + j) % stepSize) + 1) * stepSize / 180;
            double compression = curveCompress + 1/M_PI_4;
            int sinValue = round(amplitude * sin(compression * radian ));

            // set pole coordinate to zero
            p2 = p2 * poleReset;
            // set new pole coordinate
            p2 += *poleDirection * (poleOffset + sinValue);

            // get color for point depending on the reference direction
            Color color = getColor(lastValue <= (poleDirection->x*p2.x)+(poleDirection->y*p2.y)+(poleDirection->z*p2.z));
            lastValue = (poleDirection->x*p2.x)+(poleDirection->y*p2.y)+(poleDirection->z*p2.z);
            
            // set point to frame
            frame->set(p2.x, p2.y, p2.z, color.red, color.green, color.blue);

            // increment ref coordinate
            p2 += *referenceDirection;
        }

        // increment plane coordinate
        p2 += plane;
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
