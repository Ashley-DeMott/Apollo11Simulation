#include "Lander.h"

void Lander::update(const Interface* pUI, double t) {
    // If the Lander has not yet landed,
    if (!landed) {
        // Add acceleration due to gravity (x and y directions), Angle = 0, with Gravity pulling the LM down
        a.setX(computeHorizontalComponent(0, GRAVITY));
        a.setY(computeVerticalComponent(0, GRAVITY));

        // Get user input, sets which thrusters are on
        this->getUserInput(pUI);

        // Add thrust, turn left and right
        if (rotateRight) {
            rotate(-ROTATION);
        }
        if (rotateLeft) {
            rotate(ROTATION);
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

void Lander::land(bool safelyLanded) {
    // The Lander has landed, no more flying
    landed = true;

    // Turn off all thrusters
    thrust = false;
    rotateLeft = false;
    rotateRight = false;

    // If the Lander has landed safely
    if (safelyLanded) {
        // Set the Lander upright
        angle.setRadians(0);
    }
    else {
        // Set the Lander upside down
        angle.setRadians(M_PI);
    }
}

void Lander::getUserInput(const Interface* pUI) {
    rotateRight = pUI->isRight() && fuel >= ROTATE_FUEL;
    rotateLeft = pUI->isLeft() && fuel >= ROTATE_FUEL;
    thrust = pUI->isUp() && fuel >= THRUST_FUEL;
}

// Second Lander controls
void LanderWASD::getUserInput(const Interface* pUI) {
    rotateRight = pUI->isD() && fuel >= ROTATE_FUEL;
    rotateLeft = pUI->isA() && fuel >= ROTATE_FUEL;
    thrust = pUI->isW() && fuel >= THRUST_FUEL;
}

void Lander::addThrust() {
    // Calculate acceleration based on thrust and mass (F = m * a)
    double accThrust = computeAcceleration(THRUST, WEIGHT);

    // Add it to the x and y accelerations, with the Landar's current angle
    a.addX(computeHorizontalComponent(angle.getRadians() - M_PI, accThrust));
    a.addY(computeVerticalComponent(angle.getRadians(), accThrust));

    // Decrease fuel
    fuel -= THRUST_FUEL;
}
 
void Lander::rotate(double r) {
    // Update the Lander's Angle (in radians)
    angle.setRadians(angle.getRadians() + r);

    // Decrease fuel
    fuel -= ROTATE_FUEL;
}