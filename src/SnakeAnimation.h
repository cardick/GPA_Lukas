#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef SnakeAnimation_h
#define SnakeAnimation_h

#include "Animation.h"
#include "Vector.h"

struct Snake {

    public:
        Snake(int length) {
            this->length = length;
            p = (struct Point3D*) malloc((length+1) * sizeof(struct Point3D));
            //p = new Point3D[length+1];
        }

        ~Snake() {
            // delete the array of points
            delete p;
        }

        Point3D * getFirst() {
            return &p[0];
        }

        void set(Point3D p) {
            // shift all points by one, begin at the end
            for (int i = length; i > 0 ; i--)
            {
                this->p[i] = this->p[i-1];
            }
            // Vector::printPoint(&p);
            // set first element
            this->p[0] = p;
            Vector::printPoint(&this->p[0]);
        }

        Point3D * getLast() {
            return &p[length-1];
        }

        Point3D * getLost() {
            return &p[length];
        }

        int getLength() {
            return this->length;
        }

    private:
        Point3D * p;
        int length;

        // TODO: Snake grow every 5 steps
        void grow(Point3D p) {

        }
};

class SnakeAnimation : public Animation {
    public:
        void run();
    private:
        void moveForward(Snake *snake, Vector3D *v, int steps);
        void changeDirAndMoveForward(Point3D *p, Vector3D *v, const int steps);
        void makeLoop(Point3D *p);
        uint8_t randomDirection();
        bool isPossibleDirection(const Point3D *p, const Vector3D *v);
        bool isInBoundary(const Point3D *p);
        void printVector(const Vector3D *vec);
};

#endif