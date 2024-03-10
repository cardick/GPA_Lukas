#include "Eraser.h"
#include "LightCube.h"
#include "Frame.h"
#include "Graphics.h"
#include "Coloring.h"
#include "Color.h"

void Eraser::eraseRightToLeft(unsigned long speed, bool onReturn, Coloring* coloring)
{
    LightCube::getInstance().getFrame()->setPrepare();

    // move 
    for(int i=0;i<LightCube::getInstance().getRowSize();i++) {
        LightCube::getInstance().getFrame()->setPrepare();
        for (int j = 0; j < LightCube::getInstance().getColSize(); j++)
        {
            Graphics::drawColumn(i+(j*LightCube::getInstance().getColSize()), *coloring);

            // turn off the row plane behind
            if(i > 0 && !onReturn) {
                Graphics::drawColumn(i-1+(j*LightCube::getInstance().getColSize()), *offColoring);
            }
        }
        LightCube::getInstance().getFrame()->activate(getFrameCount(speed));
        wait();
    }
    for(int i=LightCube::getInstance().getRowSize()-1; i>=0; i--) {
        LightCube::getInstance().getFrame()->setPrepare();
        for (int j = 0; j < LightCube::getInstance().getColSize(); j++)
        {
            Graphics::drawColumn(i+(j*LightCube::getInstance().getColSize()), *coloring);

            if(i < LightCube::getInstance().getRowSize()-1) {
                Graphics::drawColumn(i+1+(j*LightCube::getInstance().getColSize()), *offColoring);
            }
        }
        LightCube::getInstance().getFrame()->activate(getFrameCount(speed));
        wait();
    }
}


void Eraser::eraseBackToFront(unsigned long speed, bool onReturn, Coloring* coloring)
{
    // set the first column plane
    for(int i=0;i<LightCube::getInstance().getColSize();i++) {
        LightCube::getInstance().getFrame()->setPrepare();
        for (int j = 0; j < LightCube::getInstance().getRowSize(); j++)
        {
            Graphics::drawColumn((i*LightCube::getInstance().getRowSize())+j, *coloring);

            // turn off the column plane behind
            if(i > 0 && !onReturn) {
                Graphics::drawColumn(((i-1)*LightCube::getInstance().getColSize())+j, *offColoring);
            }
        }
        LightCube::getInstance().getFrame()->activate(getFrameCount(speed));
        wait();
    }

    // move column plane along the rows
    for(int i = LightCube::getInstance().getColSize()-1; i>=0; i--) {
        LightCube::getInstance().getFrame()->setPrepare();
        for (int j = 0; j < LightCube::getInstance().getRowSize(); j++)
        {
            Graphics::drawColumn((i*LightCube::getInstance().getRowSize())+j, *coloring);

            // turn off column plane behind
            if(i < LightCube::getInstance().getColSize()-1) {
                Graphics::drawColumn(((i+1)*LightCube::getInstance().getColSize())+j, *offColoring);
            }
        }
        LightCube::getInstance().getFrame()->activate(getFrameCount(speed));
        wait();
    }    
}

void Eraser::eraseDownToUp(unsigned long speed, bool onReturn, Coloring* coloring)
{
     for (int i = 0; i < LightCube::getInstance().getLayerSize(); i++)
    {
        LightCube::getInstance().getFrame()->setPrepare();
        Graphics::drawLayer(i, *coloring);
        if(i > 0 && !onReturn) {
            Graphics::drawLayer(i-1, *offColoring);
        }
        LightCube::getInstance().getFrame()->activate(getFrameCount(speed));
        wait();
    }

    // move down
    for (int i = LightCube::getInstance().getLayerSize()-1; i >= 0; i--)
    {
        LightCube::getInstance().getFrame()->setPrepare();
        Graphics::drawLayer(i, *coloring);
        if(i < 7) {
            Graphics::drawLayer(i+1, *offColoring);
        }

        LightCube::getInstance().getFrame()->activate(getFrameCount(speed));
        wait();
    }
}

Eraser::Eraser()
{
    offColoring = new SolidColoring();
    ((SolidColoring*)offColoring)->setColor(Color(Off, Off, Off));
}

Eraser::~Eraser()
{
    delete this->offColoring;
}

void Eraser::run()
{
    SolidColoring coloring = SolidColoring();
    coloring.setColor(Color(Full, Medium, Off));
    run(static_cast<int>(random(100)%3), &coloring, false, 100);
}

void Eraser::run(int type, Coloring* coloring, bool eraseOnReturn, unsigned long speed)
{
    if (type == LTR){
        eraseRightToLeft(speed, eraseOnReturn, coloring);
    }

    if (type == BTF){
        eraseBackToFront(speed, eraseOnReturn, coloring);
    }

    if (type == DTU)
    {
        eraseDownToUp(speed, eraseOnReturn, coloring);
    }

    // turn all off, when finished
    LightCube::getInstance().getFrame()->setAllOff();
    LightCube::getInstance().getFrame()->activate(1);
    wait();
}