#pragma once
#include "point.h"
#include <cassert>

/*********************************
 * LANDER
 * The moon lander itself will keep track of its position,
 * velocity, angle, and fuel.
 *********************************/
class Lander {
public:
    // Constructor
    Lander(Point p = Point(0.0, 0.0)) : pos(p.getX(), p.getY()), angle(0.0), vel(0.0), fuel(5000) {
    }
   
    // Get position of the lander
    Point* getPos() {
        return &pos;
    }

    // Add given x and y values to the lander's position
    void addPos(double x, double y) {
        this->pos.addX(x);
        this->pos.addY(y);
    }

    // Get the angle of the Lander
    double getAngle() {
        return angle;
    }

    // Get the velocity of the Lander
    double getVel() {
        return vel;
    }

    // Get the remaining fuel of the Lander
    double getFuel() {
        return fuel;
    }

private:
    Point pos; // The position of the Lander
    double angle; // The angle of the Lander
    int fuel; // The fuel of the Lander
    double vel; // The velocity of the Lander
};