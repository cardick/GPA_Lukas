#include "CubeCheck.h"

#include <math.h>
#include "LightCube.h"
#include "Frame.h"
#include "Coloring.h"
#include "Graphics.h"
#include "Voxel.h"

void CubeCheck::run()
{
    memFree();
    // long millis = 90;
    // this->testColumns();
    // this->allOff();
    // this->testBlockWise();
    // this->testRowPlanes(millis);
    // this->allOff();
    // this->testColumnPlanes(millis);
    // this->allOff();
    // this->testLayer(millis);
    this->allOff();
    // this->testColorSpace(2000);
    // this->allOff();
    this->testSphere();
    this->testRotation();

}

void CubeCheck::testCubeFunctionality()
{
    uint8_t fadeInOut[] = {Medium, High, Full, High, Medium, Off};
    Color _c =  Color(Off, Off, Off);
    long upperBound = (LightCube::getInstance().getColSize() * LightCube::getInstance().getRowSize()) - 1;
    long rndIndex = random(0, upperBound);

    for (uint8_t i : fadeInOut)
    {
        _c.red = (Brightness) i;
        _c.green = (Brightness) i;
        Graphics::drawColumn(rndIndex, _c, 500);
    }

}

void CubeCheck::testBlockWise()
{
    Color colors[] = {
        Color(Medium, Off, Off), Color(High, Off, Off), Color(Medium, Off, Off), Color(Off, Off, Off),
        Color(Off, Medium, Off), Color(Off, High, Off), Color(Off, Medium, Off), Color(Off, Off, Off), 
        Color(Off, Off, Medium), Color(Off, Off, High), Color(Off, Off, Medium), Color(Off, Off, Off)
        
    };

    Frame * frame = LightCube::getInstance().getFrame();
    SolidColoring coloring = SolidColoring();

    for(int i = 0; i < 16; i++) {
        for(Color c : colors) {
            coloring.setColor(c);
            int startColumn = i * 4;
            frame->setPrepare();
            Graphics::drawColumn(startColumn, coloring);
            Graphics::drawColumn(startColumn + 1, coloring);
            Graphics::drawColumn(startColumn + 2, coloring);
            Graphics::drawColumn(startColumn + 3, coloring);
            frame->activate(15);
            wait();
        }
    }
}

void CubeCheck::testColumns()
{
    Frame * frame = LightCube::getInstance().getFrame();
    SolidColoring color = SolidColoring();
    color.setColor( Color(High, High, High));

    for(int i = 0; i < 64; i++) {
        frame->setPrepare();
        frame->setAllOff();
        Graphics::drawColumn(i, color);
        frame->activate(15);
        wait();
    }
}

void CubeCheck::testColumnPlanes(long millis)
{
    Frame * frame = LightCube::getInstance().getFrame();
    SolidColoring color = SolidColoring();
    color.setColor( Color(High, High, High));
    for(int i=0;i<LightCube::getInstance().getColSize();i++) {
        frame->setPrepare();
        frame->setAllOff();
        for (int j = 0; j < LightCube::getInstance().getRowSize(); j++)
        {
            Graphics::drawColumn((i*LightCube::getInstance().getRowSize())+j, color);
        }
        frame->activate(getFrameCount(millis));
        wait();
    }
    for(int i = LightCube::getInstance().getColSize()-1; i>=0; i--) {
        frame->setPrepare();
        frame->setAllOff();
        for (int j = 0; j < LightCube::getInstance().getRowSize(); j++)
        {
            Graphics::drawColumn((i*LightCube::getInstance().getRowSize())+j, color);
        }
        frame->activate(getFrameCount(millis));
        wait();
    }
}

void CubeCheck::testRowPlanes(long millis)
{
    Frame * frame = LightCube::getInstance().getFrame();
    SolidColoring color = SolidColoring();
    color.setColor( Color(High, High, High));

    for(int i=0;i<LightCube::getInstance().getRowSize();i++) {
        frame->setPrepare();
        frame->setAllOff();
        for (int j = 0; j < LightCube::getInstance().getColSize(); j++)
        {
            Graphics::drawColumn(i+(j*LightCube::getInstance().getColSize()), color);
        }
        frame->activate(getFrameCount(millis));
        wait();
    }
    for(int i=LightCube::getInstance().getRowSize()-1; i>=0; i--) {
        frame->setPrepare();
        frame->setAllOff();
        for (int j = 0; j < LightCube::getInstance().getColSize(); j++)
        {
            Graphics::drawColumn(i+(j*LightCube::getInstance().getColSize()), color);
        }
        frame->activate(getFrameCount(millis));
        wait();
    }
}

void CubeCheck::testLayer(long millis)
{
    for (int i = 0; i < LightCube::getInstance().getLayerSize(); i++)
    {
        LightCube::getInstance().getFrame()->setPrepare();
        LightCube::getInstance().getFrame()->setAllOff();
        Graphics::drawLayer(i, Color(High, High, High));
        LightCube::getInstance().getFrame()->activate(getFrameCount(millis));
        wait();
    }
    for (int i = LightCube::getInstance().getLayerSize()-1; i >= 0; i--)
    {
        LightCube::getInstance().getFrame()->setPrepare();
        LightCube::getInstance().getFrame()->setAllOff();
        Graphics::drawLayer(i, Color(High, High, High));
        LightCube::getInstance().getFrame()->activate(getFrameCount(millis));
        wait();
    }
}

void CubeCheck::testColorSpace(long millis)
{
    // spanning the color space
    Frame *f = LightCube::getInstance().getFrame();
    Coloring* space = new ColorSpace(f->getRows(), f->getCols(), f->getLayers());
    Voxel vox = Voxel();
    Color color = Color();

    f->setPrepare();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                vox = Voxel(i,j,k);
                color = space->getColor(vox);
                f->set(vox.x, vox.y, vox.z, color.red, color.green, color.blue);
            }
        }
    }
    f->activate(getFrameCount(millis));
    wait();
}

void CubeCheck::testSphere()
{
    // SolidColoring c = SolidColoring();
    // c.setColor(Color(High, Medium, Off));
    Coloring * c = new ColorSpace(8,8,8);

    Frame *frame = LightCube::getInstance().getFrame();

    // for(float i=1.45; i<8; i+=2) {
        frame->setPrepare();
        Graphics::drawSphere(5.45, *c, frame);
        // if(i>7) {
            frame->activate(getFrameCount(2000));
        // } else {
        //     frame->activate(getFrameCount(90));
        // }
        wait();
    // }
}

void CubeCheck::testRotation()
{
    unsigned long start_time = millis();
    while (millis() < (start_time*60000))
    {
        Graphics::rotate((Direction)(Up|Right), 360, 300);
    }
}

void CubeCheck::moveFrontBack()
{
    SolidColoring coloring = SolidColoring();
    coloring.setColor(Color(High, Off, Medium));

    Frame *f = LightCube::getInstance().getFrame();
    f->setPrepare();
    Graphics::erase();

    for (int i = 0; i < 8; i++)
    {

        f->setPrepare();
        Graphics::erase();

        LightCube::getInstance().getFrame()->set(i, 1, 1, High, Medium, Off);
        LightCube::getInstance().getFrame()->set(i, 1, 2, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 1, 3, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 1, 4, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 1, 5, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 1, 6, High, Medium, Off);

        LightCube::getInstance().getFrame()->set(i, 2, 1, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 3, 1, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 4, 1, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 5, 1, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 6, 1, High, Medium, Off);

        LightCube::getInstance().getFrame()->set(i, 6, 2, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 6, 3, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 6, 4, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 6, 5, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 6, 6, High, Medium, Off);

        LightCube::getInstance().getFrame()->set(i, 2, 6, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 3, 6, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 4, 6, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 5, 6, High, Off, Medium);

        LightCube::getInstance().getFrame()->set(i, 3, 3, High, Medium, Medium);
        LightCube::getInstance().getFrame()->set(i, 3, 4, High, Medium, Medium);
        LightCube::getInstance().getFrame()->set(i, 4, 3, High, Medium, Medium);
        LightCube::getInstance().getFrame()->set(i, 4, 4, High, Medium, Medium);

        if (i == 0 || i == 7)
        {
            f->activate(getFrameCount(500));
        }
        else
        {
            f->activate(getFrameCount(100));
        }
        wait();
    }

    for (int i = 6; i >= 0; i--)
    {
        f->setPrepare();
        Graphics::erase();

        LightCube::getInstance().getFrame()->set(i, 1, 1, High, Medium, Off);
        LightCube::getInstance().getFrame()->set(i, 1, 2, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 1, 3, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 1, 4, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 1, 5, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 1, 6, High, Medium, Off);

        LightCube::getInstance().getFrame()->set(i, 2, 1, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 3, 1, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 4, 1, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 5, 1, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 6, 1, High, Medium, Off);

        LightCube::getInstance().getFrame()->set(i, 6, 2, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 6, 3, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 6, 4, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 6, 5, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 6, 6, High, Medium, Off);

        LightCube::getInstance().getFrame()->set(i, 2, 6, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 3, 6, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 4, 6, High, Off, Medium);
        LightCube::getInstance().getFrame()->set(i, 5, 6, High, Off, Medium);

        LightCube::getInstance().getFrame()->set(i, 3, 3, High, Medium, Medium);
        LightCube::getInstance().getFrame()->set(i, 3, 4, High, Medium, Medium);
        LightCube::getInstance().getFrame()->set(i, 4, 3, High, Medium, Medium);
        LightCube::getInstance().getFrame()->set(i, 4, 4, High, Medium, Medium);

        if (i == 0)
        {
            f->activate(getFrameCount(500));
        }
        else
        {
            f->activate(getFrameCount(100));
        }
        wait();
    }
    f->reset();
}

void CubeCheck::rotateCross()
{
    //Graphics::drawColumn(3, )
}

void CubeCheck::allOff()
{
    LightCube::getInstance().getFrame()->setAllOff();
    LightCube::getInstance().getFrame()->activate(1);
    wait();
}