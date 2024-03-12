#include "Eraser.h"
#include "LightCube.h"
#include "Frame.h"
#include "Graphics.h"
#include "Coloring.h"
#include "Color.h"

void Eraser::eraseRightToLeft(unsigned long speed, bool onReturn, Coloring* coloring)
{
    left(speed, onReturn, coloring);
    right(speed, onReturn, coloring);
}


void Eraser::eraseBackToFront(unsigned long speed, bool onReturn, Coloring* coloring)
{
    front(speed, onReturn, coloring);
    back(speed, onReturn, coloring);
}

void Eraser::eraseDownToUp(unsigned long speed, bool onReturn, Coloring* coloring)
{
    up(speed, onReturn, coloring);
    down(speed, onReturn, coloring);
}

Eraser::Eraser()
{
    offColoring = new SolidColoring();
    ((SolidColoring*)offColoring)->setColor(Color(Off, Off, Off));
}

Eraser::~Eraser()
{
    delete offColoring;
}

void Eraser::run()
{
    SolidColoring coloring = SolidColoring();
    coloring.setColor(Color(Full, Medium, Off));
    run(static_cast<int>(random(100)%3), &coloring, false, 100);
}

void Eraser::run(int type, Coloring* coloring, bool eraseOnReturn, unsigned long speed)
{
    //memFree();
    
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

void Eraser::front(unsigned long speed, bool onReturn, Coloring *coloring)
{
    uint8_t colSize = LightCube::getInstance().getColSize();
    uint8_t rowSize = LightCube::getInstance().getRowSize();
    uint8_t draw, erase = -1;

    // set the first column plane
    for(int i=0; i < colSize; i++) {
        LightCube::getInstance().getFrame()->setPrepare();
        for (int j = 0; j < rowSize; j++)
        {
            draw = (i*rowSize)+j;
            // turn off the column plane behind
            if(i > 0 && !onReturn) {
                erase = ((i-1)*colSize)+j;
            }
            drawColumns(draw, erase, coloring);
        }
        LightCube::getInstance().getFrame()->activate(getFrameCount(speed));
        wait();
    }
}

void Eraser::back(unsigned long speed, bool onReturn, Coloring *coloring)
{
    uint8_t colSize = LightCube::getInstance().getColSize();
    uint8_t rowSize = LightCube::getInstance().getRowSize();
    uint8_t draw, erase = -1;

    // move column plane along the rows
    for(int i = colSize-1; i>=0; i--) {
        LightCube::getInstance().getFrame()->setPrepare();
        for (int j = 0; j < rowSize; j++)
        {
            draw = (i*rowSize)+j;
            // turn off column plane behind
            if(i < colSize-1) {
                erase = ((i+1)*colSize)+j;
            }
            drawColumns(draw, erase, coloring);
        }
        LightCube::getInstance().getFrame()->activate(getFrameCount(speed));
        wait();
    }
}

void Eraser::left(unsigned long speed, bool onReturn, Coloring *coloring)
{
    uint8_t colSize = LightCube::getInstance().getColSize();
    uint8_t draw, erase = -1;

    // move 
    for(int i=0;i<LightCube::getInstance().getRowSize();i++) {
        LightCube::getInstance().getFrame()->setPrepare();
        for (int j = 0; j < colSize; j++)
        {
            draw = i + (j*colSize);
            // turn off the row plane behind
            if(i > 0 && !onReturn) {
                erase = i-1+(j*colSize);
            }
            drawColumns(draw, erase, coloring);
        }
        LightCube::getInstance().getFrame()->activate(getFrameCount(speed));
        wait();
    }
}

void Eraser::right(unsigned long speed, bool onReturn, Coloring *coloring)
{
    uint8_t colSize =  LightCube::getInstance().getColSize();
    uint8_t rowSize = LightCube::getInstance().getRowSize();
    uint8_t draw, erase = -1;

    for(int i=rowSize-1; i>=0; i--) {
        LightCube::getInstance().getFrame()->setPrepare();
        for (int j = 0; j < colSize; j++)
        {
            draw = i+(j*colSize);
            if(i < rowSize-1) {
                erase =i+1+(j*colSize);
            }
            drawColumns(draw, erase, coloring);
        }
        LightCube::getInstance().getFrame()->activate(getFrameCount(speed));
        wait();
    }
}

void Eraser::up(unsigned long speed, bool onReturn, Coloring *coloring)
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
}

void Eraser::down(unsigned long speed, bool onReturn, Coloring *coloring)
{
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

void Eraser::drawColumns(uint8_t drawColumn, uint8_t eraseColumn, Coloring *coloring) {
    Graphics::drawLayer(drawColumn, *coloring);
    if(eraseColumn < (LightCube::getInstance().getColSize()*LightCube::getInstance().getRowSize())) {
        Graphics::drawLayer(eraseColumn, *offColoring);
    }
}