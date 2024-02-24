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
    Vector3D * richtung = new Vector3D();
    VectorClass::setDirection(richtung, Front|Up);
    //Graphics::drawLine(punkt, richtung, 5);
   // Die hinterste Matrix bekommt einen ausen rahmen der dann nach zeit(x) um eine Matrix nach forne rückt. die jetzt hintere matrix wird dann mit einem um eine reihe engerem rahmen
   //(ausgefült) dann wir wirder nach zeit(x) weitergefürt. bis die erste matrix also der außen rahmen an der fordesten Matrix ist, dann geht der äusere rahmen aus und der zweite rahmen
   //geht an die erste matrix und das ganze geht dann so bis die ganz enge Matrix ganz forne ist dann könnte die erste Matrix komplett weiß werden und die ganze animation fängt von 
   // forne an.
    
}























