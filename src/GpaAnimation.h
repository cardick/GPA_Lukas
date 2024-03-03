#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef GpaAnimation_h
#define GpaAnimation_h

#include "Animation.h"
#include "Vector.h"

class GpaAnimation : public Animation {
    public:
        void run();
        void run(unsigned long millis);
    private:
        void moveTunnel(Frame *frame);
        void moveTunnelBack(Frame *frame);
        void snake(long millis);

        void changeDir(Point3D *p, const Direction dir, const int steps);
        void moveForward(Point3D *p, const Vector3D *v, int steps);
        void makeLoop(Point3D *p);

        bool isPossibleDirection(const Vector3D *vec);
        bool isInBoundary(const Point3D *p);
        unsigned long currentMillis();

};

#endif