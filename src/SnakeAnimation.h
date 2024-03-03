#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef SnakeAnimation_h
#define SnakeAnimation_h

#include "Animation.h"
#include "Vector.h"

class SnakeAnimation : public Animation {
    public:
        void run();
    private:
        void moveForward(Point3D *p, const Vector3D *v, int steps);
        void changeDirAndMoveForward(Point3D *p, Vector3D *v, const int steps);
        void makeLoop(Point3D *p);
        Direction randomDirection();
        bool isPossibleDirection(const Point3D *p, const Vector3D *v);
        bool isInBoundary(const Point3D *p);
};

#endif