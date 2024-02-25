#include "GPA_Animation.h"

#include "LightCube.h"
#include "Frame.h"
#include "Coloring.h"
#include "Graphics.h"
#include "Vector.h"

void GpaAnimation::run()
{
    // start coding here
    Serial.println("Hello Animation");
    Graphics::drawColumn(8, Color(High, Low, High), 500);

    // was möchte ich, das der Würfel tut
    Point3D punkt = {0,6,4};

   // Die hinterste Matrix bekommt einen aussen rahmen der dann nach zeit(x) um eine Matrix nach vorne rückt. 

    // prepare frame

    // drawRectangle - outer lines is Point3D(0,0,0), drirectionA = Up, directionB = Right, lengthA = 8, lengthB = 8
    
    // getFrameCount(200);
    // activate frame 
    // wait();

   // die jetzt hintere matrix wird dann mit einem um eine reihe engerem rahmen (ausgefült) 
   // dann wird wieder nach zeit(x) weitergefürt. bis die erste matrix also der außen rahmen an der fordesten Matrix ist, 
   // dann geht der äussere rahmen aus und der zweite rahmen geht an die erste matrix und 
   // das ganze geht dann so bis die ganz enge Matrix ganz vorne ist 
   // dann könnte die erste Matrix komplett weiß werden und die ganze animation fängt von vorne an.
    
}























