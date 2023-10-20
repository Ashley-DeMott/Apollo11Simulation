#pragma once
#include "angle.h"
#include "uiInteract.h"

// Constants for the Lander
#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)

// The default values for the lander
const int STARTING_FUEL = 5000;
const int WIDTH = 2;
const int THRUST_FUEL = 10;
const int ROTATE_FUEL = 1;

// How far the lander rotates when the user presses left or right
const double ROTATION = 0.1;

/*********************************
 * LANDER
 * The moon lander itself will keep track of its position,
 * velocity, angle, and fuel.
 *********************************/
class Lander {
public:
    // Constructor
    Lander(Point p = Point(0.0, 0.0)) : pos(p.getX(), p.getY()), angle(0.0), v(Point(0.0, 0.0)), a(Point(0.0, 0.0)), fuel(STARTING_FUEL), thrust(false), width(WIDTH), landed(false), rotateRight(false), rotateLeft(false) {}

    // Update the position of the Lander given user input and how long it has been
    void update(const Interface* pUI, double t);

    // Called when the Lander has landed on the Ground
    void land(bool safelyLanded);

    // GETTERS //

    // If the Lander has landed
    bool hasLanded() { return landed; }

    // Get position of the lander
    Point* getPos() { return &pos; }

    // Get the overall velocity of the Lander
    double getVel() { return computeTotalComponent(v.getX(), v.getY()); }

    // Get the angle of the Lander (in radiasn)
    Angle* getAngle() { return &angle; }

    // Get the remaining fuel of the Lander
    int getFuel() { return fuel; }
    
    // Get the width of the Lander
    int getWidth() { return width; }

    // If the Lander's main thruster is on
    bool getThrust() { return thrust; }

    // If the Lander is turning left
    bool getRotateLeft() { return rotateLeft; }

    // If the Lander is turning right
    bool getRotateRight() { return rotateRight; }

protected:
    Point pos;      // The position of the Lander (x and y)
    Point v;        // The total velocity of the Lander
    Point a;        // The total acceleration of the Lander

    Angle angle;    // The angle of the Lander
    int fuel;       // The fuel of the Lander
    int width;      // The Lander's width in meters

    // If the Lander has landed on the Ground
    bool landed; 

    // If the thrust is on
    bool thrust;    

    // If the Lander is turning left or right
    bool rotateRight;
    bool rotateLeft;

    // Get movement input from the user
    virtual void getUserInput(const Interface* pUI);

    // Add accelertation from thrust to the Lander
    void addThrust();

    // Rotate the Lander left or right
    void rotate(double r);

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
        return sqrt((x * x) + (y * y));
    }
};

class LanderWASD : Lander {
public:
    // Constructor
    LanderWASD(Point p = Point(0.0, 0.0)) : Lander(p) {}

private:
    void getUserInput(const Interface* pUI);
};