#pragma once
#include "point.h"
#include "angle.h"
#include <cassert>
#include "uiInteract.h"
#define _USE_MATH_DEFINES
#include <math.h>

// Constants for the Lander
#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)

// The default values for the lander
const int STARTING_FUEL = 5000;
const int WIDTH = 2;
const int THRUST_FUEL = 10;
const int ROTATE_FUEL = 1;


/*********************************
 * LANDER
 * The moon lander itself will keep track of its position,
 * velocity, angle, and fuel.
 *********************************/
class Lander {
public:
    // Constructor
    Lander(Point p = Point(0.0, 0.0)) : pos(p.getX(), p.getY()), angle(0.0), v(Point(0.0, 0.0)), a(Point(0.0, 0.0)), fuel(STARTING_FUEL), thrust(false), width(WIDTH), landed(false) { }

    // Update the position of the Lander given user input and how long it has been
    void update(const Interface* pUI, double t) {
        // If the Lander has not yet landed,
        if (!landed) {
            // Add acceleration due to gravity (x and y directions), Angle = 0, with Gravity pulling the LM down
            a.setX(computeHorizontalComponent(0, GRAVITY));
            a.setY(computeVerticalComponent(0, GRAVITY));

            getUserInput(pUI);

            // Add thrust, turn left and right
            if (rotateRight) {
                rotate(-0.1);
            }
            if (rotateLeft) {
                rotate(0.1);
            }
            if (thrust) {
                addThrust();
            }

            // Recalculate velocity using new acceleration
            v.setX(computeVelocity(v.getX(), a.getX(), t));
            v.setY(computeVelocity(v.getY(), a.getY(), t));

            // Recalulate position using new velocity and acceleration
            pos.setX(computeDistance(pos.getX(), v.getX(), a.getX(), t));
            pos.setY(computeDistance(pos.getY(), v.getY(), a.getY(), t));
        }
    }

    // Called when the Lander has landed on the Ground
    void land() {
        // The Lander has landed, no more flying
        landed = true;

        // Turn off all thrusters
        thrust = false;
        rotateLeft = false;
        rotateRight = false;

        // Set the Lander upside down
        angle.setRadians(M_PI); 
    }

    bool hasLanded() {
        return landed;
    }
    
    // GETTERS //

    // Get position of the lander
    Point* getPos() {
       return &pos;
    }

    // Get the overall velocity of the Lander
    double getVel() {
       return computeTotalComponent(v.getX(), v.getY());
    }

    // Get the angle of the Lander (in radiasn)
    Angle* getAngle() {
        return &angle;
    }

    // Get the remaining fuel of the Lander
    int getFuel() {
        return fuel;
    }

    int getWidth() {
        return width;
    }

    bool getThrust() {
        return thrust;
    }

    bool getRotateLeft() {
        return rotateLeft;
    }

    bool getRotateRight() {
        return rotateRight;
    }

private:
    Point pos; // The position of the Lander (x and y)
    Point v; // The total velocity of the Lander
    Point a; // The total acceleration of the Lander

    Angle angle; // The angle of the Lander
    int fuel; // The fuel of the Lander
    bool thrust; // If the thrust is on
    int width; // The Lander's width in meters

    // If the Lander is turning left or right
    bool rotateRight = false;
    bool rotateLeft = false;

    // If the Lander has landed on the Ground
    bool landed;

    // Get movement from the user
    void getUserInput(const Interface* pUI) {
        rotateRight = pUI->isRight() && fuel >= ROTATE_FUEL;
        rotateLeft = pUI->isLeft() && fuel >= ROTATE_FUEL;
        thrust = pUI->isUp() && fuel >= THRUST_FUEL;
    }

    // Add accelertation from thrust to the Lander
    void addThrust() {
       // Calculate acceleration based on thrust and mass (F = m * a)
       double accThrust = computeAcceleration(THRUST, WEIGHT);

       // Add it to the x and y accelerations, with the Landar's current angle
       a.addX(computeHorizontalComponent(angle.getRadians() - M_PI, accThrust));
       a.addY(computeVerticalComponent(angle.getRadians(), accThrust));

       // Decrease fuel
       fuel -= THRUST_FUEL;
    }

    // Rotate the Lander left or right
    void rotate(double r) {
       // Update the Lander's Angle (in radians)
       angle.setRadians(angle.getRadians() + r);

       // Decrease fuel
       fuel -= ROTATE_FUEL;
    }

    // MATH METHODS //

    /***************************************************
     * COMPUTE DISTANCE
     * Apply inertia to compute a new position using the distance equation.
     * The equation is:
     *     s = s + v t + 1/2 a t^2
     * INPUT
     *     s : original position, in meters
     *     v : velocity, in meters/second
     *     a : acceleration, in meters/second^2
     *     t : time, in seconds
     * OUTPUT
     *     s : new position, in meters
     **************************************************/
    double computeDistance(double s, double v, double a, double t) {
       return s + (v * t) + 0.5 * a * (t * t);
    }

    /**************************************************
    * COMPUTE ACCELERATION
    * Find the acceleration given a thrust and mass.
    * This will be done using Newton's second law of motion:
    *     f = m * a
    * INPUT
    *     f : force, in Newtons (kg * m / s^2)
    *     m : mass, in kilograms
    * OUTPUT
    *     a : acceleration, in meters/second^2
    ***************************************************/
    double computeAcceleration(double f, double m) {
       return f / m;
    }

    /***********************************************
    * COMPUTE VELOCITY
    * Starting with a given velocity, find the new
    * velocity once acceleration is applied. This is
    * called the Kinematics equation. The
    * equation is:
    *     v = v + a t
    * INPUT
    *     v : velocity, in meters/second
    *     a : acceleration, in meters/second^2
    *     t : time, in seconds
    * OUTPUT
    *     v : new velocity, in meters/second
    ***********************************************/
    double computeVelocity(double v, double a, double t) {
       return v + a * t;
    }

    /***********************************************
    * COMPUTE VERTICAL COMPONENT
    * Find the vertical component of a velocity or acceleration.
    * The equation is:
    *     cos(a) = y / total
    * This can be expressed graphically:
    *      x
    *    +-----
    *    |   /
    *  y |  / total
    *    |a/
    *    |/
    * INPUT
    *     a : angle, in radians
    *     total : total velocity or acceleration
    * OUTPUT
    *     y : the vertical component of the total
    ***********************************************/
    double computeVerticalComponent(double a, double total) {
       return total * cos(a);
    }

    /***********************************************
    * COMPUTE HORIZONTAL COMPONENT
    * Find the horizontal component of a velocity or acceleration.
    * The equation is:
    *     sin(a) = x / total
    * This can be expressed graphically:
    *      x
    *    +-----
    *    |   /
    *  y |  / total
    *    |a/
    *    |/
    * INPUT
    *     a : angle, in radians
    *     total : total velocity or acceleration
    * OUTPUT
    *     x : the vertical component of the total
    ***********************************************/
    double computeHorizontalComponent(double a, double total) {
       return sin(a) * total;
    }

    /************************************************
    * COMPUTE TOTAL COMPONENT
    * Given the horizontal and vertical components of
    * something (velocity or acceleration), determine
    * the total component. To do this, use the Pythagorean Theorem:
    *    x^2 + y^2 = t^2
    * where:
    *      x
    *    +-----
    *    |   /
    *  y |  / total
    *    | /
    *    |/
    * INPUT
    *    x : horizontal component
    *    y : vertical component
    * OUTPUT
    *    total : total component
    ***********************************************/
    double computeTotalComponent(double x, double y) {
       return  sqrt((x * x) + (y * y));
    }
};