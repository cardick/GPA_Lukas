#include "Eraser.h"
#include "LightCube.h"
#include "Frame.h"
#include "Graphics.h"

void Eraser::eraseRightToLeft(unsigned long speed)
{
Frame * frame = LightCube::getInstance().getFrame();
    SolidColoring color = SolidColoring();
    color.setColor( Color(High, High, High));

    // move 
    for(int i=0;i<LightCube::getInstance().getRowSize();i++) {
        frame->setPrepare();
        frame->setAllOff();
        for (int j = 0; j < LightCube::getInstance().getColSize(); j++)
        {
            Graphics::drawColumn(i+(j*LightCube::getInstance().getColSize()), color);
        }
        frame->activate(getFrameCount(speed));
        wait();
    }
    for(int i=LightCube::getInstance().getRowSize()-1; i>=0; i--) {
        frame->setPrepare();
        frame->setAllOff();
        for (int j = 0; j < LightCube::getInstance().getColSize(); j++)
        {
            Graphics::drawColumn(i+(j*LightCube::getInstance().getColSize()), color);
        }
        frame->activate(getFrameCount(speed));
        wait();
    }
}

void Eraser::eraseBackToFront(unsigned long speed)
{
     Frame * frame = LightCube::getInstance().getFrame();
    SolidColoring color = SolidColoring();
    color.setColor( Color(High, High, High));

    // set the first column plane
    for(int i=0;i<LightCube::getInstance().getColSize();i++) {
        frame->setPrepare();
        frame->setAllOff();
        for (int j = 0; j < LightCube::getInstance().getRowSize(); j++)
        {
            Graphics::drawColumn((i*LightCube::getInstance().getRowSize())+j, color);
        }
        frame->activate(getFrameCount(speed));
        wait();
    }

    // move column plane along the rows
    for(int i = LightCube::getInstance().getColSize()-1; i>=0; i--) {
        frame->setPrepare();
        frame->setAllOff();
        for (int j = 0; j < LightCube::getInstance().getRowSize(); j++)
        {
            Graphics::drawColumn((i*LightCube::getInstance().getRowSize())+j, color);
        }
        frame->activate(getFrameCount(speed));
        wait();
    }
}

void Eraser::eraseDownToUp(unsigned long speed)
{
     for (int i = 0; i < LightCube::getInstance().getLayerSize(); i++)
    {
        LightCube::getInstance().getFrame()->setPrepare();
        //LightCube::getInstance().getFrame()->setAllOff();
        Graphics::drawLayer(i, Color(High, High, High));
        if(i>0) {
            Graphics::drawLayer(i-1, Color(Off, Off, Off));
        }
        LightCube::getInstance().getFrame()->activate(getFrameCount(speed));
        wait();
    }

    // move down
    for (int i = LightCube::getInstance().getLayerSize()-1; i >= 0; i--)
    {
        LightCube::getInstance().getFrame()->setPrepare();
        LightCube::getInstance().getFrame()->setAllOff();
        Graphics::drawLayer(i, Color(High, High, High));
        LightCube::getInstance().getFrame()->activate(getFrameCount(speed));
        wait();
    }
}

void Eraser::run()
{
    run(static_cast<int>(random(100)%3), 100);
}

void Eraser::run(int type, unsigned long speed)
{
    if (type == LTR){
        eraseRightToLeft(speed);
    }

    if (type == BTF){
        eraseBackToFront(speed);
    }

    if (type == DTU)
    {
        eraseDownToUp(speed);
    }
    LightCube::getInstance().getFrame()->setAllOff();
     LightCube::getInstance().getFrame()->activate(1);
}