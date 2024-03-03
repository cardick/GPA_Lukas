#include "CubeCheck.h"

#include <math.h>
#include "LightCube.h"
#include "Frame.h"
#include "Coloring.h"
#include "Graphics.h"

void CubeCheck::run()
{
    long millis = 90;
    // this->testColumns();
    // this->allOff();
    // this->testBlockWise();
    // this->testRowPlanes(millis);
    // this->allOff();
    // this->testColumnPlanes(millis);
    // this->allOff();
    // this->testLayer(millis);
    // this->allOff();
    this->testSphere();
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
    for(int i = 0; i < 16; i++) {
        for(Color c : colors) {
            int startColumn = i * 4;
            frame->setPrepare();
            Graphics::drawColumn(startColumn, c);
            Graphics::drawColumn(startColumn + 1, c);
            Graphics::drawColumn(startColumn + 2, c);
            Graphics::drawColumn(startColumn + 3, c);
            frame->activate(15);
            wait();
        }
    }
}

void CubeCheck::testColumns()
{
    Frame * frame = LightCube::getInstance().getFrame();
    for(int i = 0; i < 64; i++) {
        frame->setPrepare();
        frame->setAllOff();
        Graphics::drawColumn(i, Color(High, High, High));
        frame->activate(15);
        wait();
    }
}

void CubeCheck::testColumnPlanes(long millis)
{
    Frame * frame = LightCube::getInstance().getFrame();
    for(int i=0;i<LightCube::getInstance().getColSize();i++) {
        frame->setPrepare();
        frame->setAllOff();
        for (int j = 0; j < LightCube::getInstance().getRowSize(); j++)
        {
            Graphics::drawColumn((i*LightCube::getInstance().getRowSize())+j, Color(High, High, High));
        }
        frame->activate(getFrameCount(millis));
        wait();
    }
    for(int i = LightCube::getInstance().getColSize()-1; i>=0; i--) {
        frame->setPrepare();
        frame->setAllOff();
        for (int j = 0; j < LightCube::getInstance().getRowSize(); j++)
        {
            Graphics::drawColumn((i*LightCube::getInstance().getRowSize())+j, Color(High, High, High));
        }
        frame->activate(getFrameCount(millis));
        wait();
    }
}

void CubeCheck::testRowPlanes(long millis)
{
    Frame * frame = LightCube::getInstance().getFrame();
    for(int i=0;i<LightCube::getInstance().getRowSize();i++) {
        frame->setPrepare();
        frame->setAllOff();
        for (int j = 0; j < LightCube::getInstance().getColSize(); j++)
        {
            Graphics::drawColumn(i+(j*LightCube::getInstance().getColSize()), Color(High, High, High));
        }
        frame->activate(getFrameCount(millis));
        wait();
    }
    for(int i=LightCube::getInstance().getRowSize()-1; i>=0; i--) {
        frame->setPrepare();
        frame->setAllOff();
        for (int j = 0; j < LightCube::getInstance().getColSize(); j++)
        {
            Graphics::drawColumn(i+(j*LightCube::getInstance().getColSize()), Color(High, High, High));
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

void CubeCheck::testSphere()
{
    SolidColoring c = SolidColoring();
    c.setColor(Color(High, Medium, Off));

    Frame *frame = LightCube::getInstance().getFrame();

    for(float i=1.45; i<8; i+=2) {
        frame->setPrepare();
        Graphics::drawSphere(i, c, frame);
        if(i>7) {
            frame->activate(getFrameCount(10000));
        } else {
            frame->activate(getFrameCount(10));
        }
        wait();
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
void CubeCheck::allOff()
{
    LightCube::getInstance().getFrame()->setAllOff();
    LightCube::getInstance().getFrame()->activate(1);
}