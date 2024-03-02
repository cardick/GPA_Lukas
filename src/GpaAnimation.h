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
    private:
        void moveTunnel(Frame *frame);
        void moveTunnelBack(Frame *frame);
        void snake(long millis);

        void changeDir(Point3D p, Direction dir, int steps, Frame *frame);
        void moveForward(Point3D p, Vector3D v, int steps, Frame *frame);
        void makeLoop(Point3D p, Frame *frame);

        bool isPossibleDirection(Vector3D vec);
        bool isInBoundary(Point3D p);
};

#endif